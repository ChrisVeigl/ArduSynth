/*
 
   Based upon "Thankyou Synth" - by Daniel Sinderson 
   https://create.arduino.cc/projecthub/scraptured/phasemod-drone-synth-w-arduino-nano-mozzi-7ab2ff

   modified for FuzzyK'iin V1 PCB by Chris Veigl
 
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

#define CONTROL_RATE 256

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
int decay = 20;
bool mode = 0;
bool noteTrigger1 = 0;
bool noteTrigger2 = 0;
bool noteTrigger3 = 0;

int  gain=0;
int freqs[3];
byte wfs[3];

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

void readPins() {
  freqs[0] = 1024-mozziAnalogRead(A0);
  freqs[1] = mozziAnalogRead(A1);
  freqs[2] = mozziAnalogRead(A2);
  
  wfs[0] = mozziAnalogRead(A3) >> 8;
  wfs[1] = mozziAnalogRead(A4) >> 8;
  wfs[2] = mozziAnalogRead(A5) >> 8;

  mod_ratio = (mozziAnalogRead(A6) >> 7) + 1;
  decay = 5000- ( mozziAnalogRead(A7) << 2);
  Serial.println(decay);

  mode = digitalRead(11);
  noteTrigger1 = digitalRead(3);
  noteTrigger2 = digitalRead(4);
  noteTrigger3 = digitalRead(5);
}

void setFrequencies() {
    int carrier_freq = kMapCarrierFreq(freqs[0]);
    if (actMode) carrier_freq*=actMode;
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
  Serial.begin(115200);
  Serial.print("Control Rate = ");  Serial.println(CONTROL_RATE);

  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  randSeed(); // fresh random, MUST be called before startMozzi - wierd bug
  startMozzi(CONTROL_RATE);
}


void updateControl() {
  static uint8_t noteTrigger1_old=1;
  static uint8_t noteTrigger2_old=1;
  static uint8_t noteTrigger3_old=1;
  static uint8_t mode_old=1;
  
  readPins();
  setWavetables();
  setFrequencies();

  if ((noteTrigger1 == 0) && (noteTrigger1_old == 1)) { 
       kEnvelope.start(decay >> 6,decay);
       digitalWrite(6,HIGH);  
       actMode=1;
  }
  if ((noteTrigger2 == 0) && (noteTrigger2_old == 1)) { 
       kEnvelope.start(decay >> 4,decay >> 1);
       digitalWrite(7,HIGH);  
       actMode=2;
  }
  if ((noteTrigger3 == 0) && (noteTrigger3_old == 1)) { 
       kEnvelope.start(decay >> 8,decay >> 1);
       digitalWrite(8,HIGH);  
       actMode=3;
  }
       
  if ((mode != mode_old) && ( mode == 0 )) { actMode=0; Serial.println("continous mode!");  }

  noteTrigger1_old=noteTrigger1;
  noteTrigger2_old=noteTrigger2;
  noteTrigger3_old=noteTrigger3;
  mode_old=mode;

  gain = (int) kEnvelope.next(); 
  if (gain==0) {       digitalWrite(6,LOW);   digitalWrite(7,LOW);   digitalWrite(8,LOW); }

  
}


int updateAudio() {
  long audio;

  long mod = aSmoothIntensity.next(fm_intensity) * modulator.next();
  if (actMode == 0) {
    audio = carrier.phMod(mod);
  }
  else {
    //Serial.println(gain);
    audio = (((long)carrier.phMod(mod) * gain)>>8);
  }
//  return audio << 6; // 14-bit number for HI-FI mode
  return audio; 
}

void loop() {
  audioHook();
}
