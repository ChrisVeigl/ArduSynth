/*
 
   Based upon "Thankyou Synth" - by Daniel Sinderson 
   https://create.arduino.cc/projecthub/scraptured/phasemod-drone-synth-w-arduino-nano-mozzi-7ab2ff

   modified for Teensynth PCB by Chris Veigl
   Teensy-LC version, with Midi support!
 
 */


#include <MozziGuts.h>
#include <Oscil.h>
#include <Smooth.h>
#include <AutoMap.h>
#include <Ead.h> // exponential attack decay
#include <mozzi_rand.h>

#include <tables/sin256_int8.h>
#include <tables/halfsin256_uint8.h>
#include <tables/waveshape1_softclip_int8.h>
#include <tables/saw256_int8.h>

#include "frequencyTable.h"

#define CONTROL_RATE 256

#define MIDI_CHANNEL 1
#define NUM_POTENTIOMETERS 8
#define NUM_KEYS 3

int pinKeys[NUM_KEYS]={4,5,6};   // TBD: change to key-pins of TeensyLC!  {7,8,9}
int pinLeds[NUM_KEYS]={7,8,9};   // TBD: change to PWM-pins of TeensyLC!  {3,4,6}
int pinPotentiometers[NUM_POTENTIOMETERS]={A1,A2,A3,A4,A5,A6,A7,A8};
int attackFactors[NUM_KEYS]={6,4,8};
int decayFactors[NUM_KEYS]={0,1,1};
int ledGainFactor = 10;

#define PIN_KEY_MODE 12         // TBD: change to key-pin of TeensyLC!  10
#define PIN_INTERNAL_LED 13
#define ANALOG_CHANGE_THRESHOLD 5
#define BYPASS_MANUAL_CONTROL_TIME 800

// VARIABLES

AutoMap kMapCarrierFreq(0,1023,20,440);
AutoMap kMapIntensity(0,1023,700,1);
AutoMap kMapModSpeed(0,1023,10000,0);
AutoMap kMapEnvelopeTimes(0, 1023, 0, 1000);

Oscil <256, AUDIO_RATE> carrier;
Oscil <256, AUDIO_RATE> modulator;
Oscil <256, CONTROL_RATE> modDepth;

Ead kEnvelope(CONTROL_RATE); // resolution will be CONTROL_RATE

int actMode=0;
int attack = 20;
int envelopeLength = 2000;
bool mode = 0;
int bypassManualControl=0;
float midiToneFrequency =0;


int  gain=0;
int freqs[3];
byte wfs[3];

int analogValues[NUM_POTENTIOMETERS]={0};
int lastAnalogValues[NUM_POTENTIOMETERS]={0};
int midiCCValues[NUM_POTENTIOMETERS]={0};
bool noteTriggers[NUM_KEYS]={0};
bool lastNoteTriggers[NUM_KEYS]={1};
bool lastMode=1;

int mod_ratio = 1; //frequency of the modulator as an integer multiple of the carrier
long fm_intensity; // carries control info from updateControl to updateAudio

float smoothness = 0.95f;
Smooth <long> aSmoothIntensity(smoothness);

// FUNCTIONS
void setWavetables() {
  if (wfs[0]==0) {carrier.setTable(SIN256_DATA);}
  else if (wfs[0]==1) {carrier.setTable(HALFSIN256_DATA);}
  else if (wfs[0]==2) {carrier.setTable(SAW256_DATA);}
  else if (wfs[0]==3) {carrier.setTable(WAVESHAPE1_SOFTCLIP_DATA);}

  if (wfs[1]==0) {modulator.setTable(SIN256_DATA);}
  else if (wfs[1]==1) {modulator.setTable(HALFSIN256_DATA);}
  else if (wfs[1]==2) {modulator.setTable(SAW256_DATA);}
  else if (wfs[1]==3) {modulator.setTable(WAVESHAPE1_SOFTCLIP_DATA);}

  if (wfs[2]==0) {modDepth.setTable(SIN256_DATA);}
  else if (wfs[2]==1) {modDepth.setTable(HALFSIN256_DATA);}
  else if (wfs[2]==2) {modDepth.setTable(SAW256_DATA);}
  else if (wfs[2]==3) {modDepth.setTable(WAVESHAPE1_SOFTCLIP_DATA);}
}

// midi note-on handler
// this maps incoming midi note-on values (per channels) to the analog potentiometer values
// and bypasses the manual potentiomenter control for a certain time
void myNoteOn(byte channel, byte note, byte velocity) {
  Serial.printf("Midi Note On: Channel %d, note %d, velocity %d\n", channel, note, velocity );
  digitalWrite(PIN_INTERNAL_LED,HIGH);
  bypassManualControl=BYPASS_MANUAL_CONTROL_TIME;
  if (channel<1) channel=1;
  if (channel>=NUM_POTENTIOMETERS) channel=NUM_POTENTIOMETERS-1;
  int val=(127-note)*8; if (val<0) val=0; else if (val>1023) val=1023;
  analogValues[channel-1]=val;
  if (channel == 1) midiToneFrequency=frequencyTable[note];
}
void myNoteOff(byte channel, byte note, byte velocity){
  Serial.printf("Midi Note Off: Channel %d, note %d, velocity %d\n", channel, note, velocity );
  digitalWrite(PIN_INTERNAL_LED,LOW);
}

void updateAnalogValues() {
  if (bypassManualControl) { 
    bypassManualControl--; 
    return; 
  }

  for (int i=0;i<NUM_POTENTIOMETERS;i++){
    analogValues[i]=analogRead(pinPotentiometers[i]);  // mozziAnalogRead(i); 
   
    analogValues[7]=512;  // TBD: remove this when poti7 is mounted!

    int difference=lastAnalogValues[i]-analogValues[i];
    if (abs(difference) > ANALOG_CHANGE_THRESHOLD) {
            
      int val=map(analogValues[i],0,1024,0,127);
      if (val != midiCCValues[i]) {
        midiCCValues[i]=val;
        lastAnalogValues[i]=analogValues[i];
        Serial.printf("Send CC %d -> %d\n",i,val);
        usbMIDI.sendControlChange(i, val, MIDI_CHANNEL);
      }
    }
  }
}

void readPins() {
  updateAnalogValues();

  freqs[0] = 1024-analogValues[0];
  freqs[1] = analogValues[1];
  freqs[2] = analogValues[2];
  
  wfs[0] = analogValues[3] >> 8;
  wfs[1] = analogValues[4] >> 8;
  wfs[2] = analogValues[5] >> 8;

  mod_ratio = (analogValues[6] >> 7) + 1;
  envelopeLength = 5000 - ( analogValues[7] << 2);

  mode = digitalRead(PIN_KEY_MODE);
  for (int i=0;i<NUM_KEYS;i++) {
    noteTriggers[i] = digitalRead(pinKeys[i]);
  }
}

void setFrequencies() {
    int carrier_freq;
    
    if (bypassManualControl) {     // control carrier frequency via midi-in
      carrier_freq = midiToneFrequency;    // get carrier frequency from last midi input (note-on)
    }
    else {   // control carrier frequency via potentiometer
      carrier_freq = kMapCarrierFreq(freqs[0]);
      if (actMode) carrier_freq*=actMode;  // modify carrier frequency according to pressed buttons
    }

    int mod_freq = carrier_freq * mod_ratio;

    int intensity_calibrated = kMapIntensity(freqs[2]);
    fm_intensity = ((long)intensity_calibrated * (modDepth.next()+128))>>8;

    float mod_speed = (float)kMapModSpeed(freqs[1])/1000;

    carrier.setFreq(carrier_freq);
    modulator.setFreq(mod_freq);
    modDepth.setFreq(mod_speed);    
}


// ################### THE GOODS! #####################

void setup() {
  delay (200);
  Serial.begin(9600);

  pinMode(PIN_KEY_MODE, INPUT_PULLUP);
  for (int i=0;i<NUM_KEYS;i++) {
    pinMode(pinKeys[i], INPUT_PULLUP);
    pinMode(pinLeds[i], OUTPUT);
  }

  pinMode(PIN_INTERNAL_LED, OUTPUT);
  pinMode(23, OUTPUT);
  digitalWrite (23, HIGH);   // send 3,3V to Potentiometers!  TBD: use correct pin for TeensyLC on PCB!

  randSeed(); // fresh random, MUST be called before startMozzi - wierd bug

  kMapCarrierFreq(0);  kMapCarrierFreq(1023);
  kMapIntensity(0);  kMapIntensity(1023);
  kMapModSpeed(0);  kMapModSpeed(1023);
  kMapEnvelopeTimes(0);  kMapEnvelopeTimes(1023);

  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);

  Serial.print("TeensySynth welcome!");
  Serial.print("Control Rate = ");  Serial.println(CONTROL_RATE);

  startMozzi(CONTROL_RATE);
  
}


void updateControl() {
  static int8_t activeKey=-1;

  usbMIDI.read();
  readPins();
  setWavetables();
  setFrequencies();

  for (int i=0;i<NUM_KEYS;i++) {
    if ((noteTriggers[i] == 0) && (lastNoteTriggers[i] == 1)) { 
         kEnvelope.start(envelopeLength >> attackFactors[i],envelopeLength >> decayFactors[i]);
         digitalWrite(pinLeds[i],HIGH);  
         activeKey=i;
         actMode=i+1;
         Serial.print("Key ");  
         Serial.print(i+1);  
         Serial.println(" pressed!");  
    }
    lastNoteTriggers[i]=noteTriggers[i];
  }
       
  if ((mode != lastMode) && ( mode == 0 )) { 
    actMode=0; 
    Serial.println("Continous mode enabled!");  
  }
  lastMode=mode;

  gain = (int) kEnvelope.next(); 
  for (int i=0;i<NUM_KEYS;i++) {
    if (i==activeKey) analogWrite(pinLeds[i],gain*ledGainFactor); else analogWrite(pinLeds[i],0);
  }
}


int updateAudio() {
  long audio;

  long mod = aSmoothIntensity.next(fm_intensity) * modulator.next();
  if (actMode == 0) {
    audio = carrier.phMod(mod);
  }
  else {
    audio = (((long)carrier.phMod(mod) * gain)>>8);
  }

  return audio<<4;  // 12-bit audio signal for TeensyLC 
}

void loop() {
  audioHook();
}
