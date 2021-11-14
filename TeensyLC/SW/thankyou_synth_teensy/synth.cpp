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

#include "globals.h"
#include "frequencyTable.h"

#include <tables/sin256_int8.h>
#include <tables/halfsin256_uint8.h>
#include <tables/waveshape1_softclip_int8.h>
#include <tables/saw256_int8.h>

extern int pinLeds[NUM_KEYS-1];    // get access to the leds!

// VARIABLES
AutoMap kMapCarrierFreq(0,1023,20,440);
AutoMap kMapIntensity(0,1023,700,1);
AutoMap kMapModSpeed(0,1023,10000,0);
AutoMap kMapEnvelopeTimes(0, 1023, 0, 1000);

Oscil <256, AUDIO_RATE> carrier;
Oscil <256, AUDIO_RATE> modulator;
Oscil <256, CONTROL_RATE> modDepth;

Ead kEnvelope(CONTROL_RATE); // resolution will be CONTROL_RATE

int freqs[3];
byte wfs[3];

int  gain=0;
int ledGainFactor = 10;
int actMode=0;
int attack = 20;
bool mode = 0;
int8_t activeKey=-1;

int attackFactors[NUM_KEYS]={6,4,8};
int decayFactors[NUM_KEYS]={0,1,1};
int envelopeLength = 2000;
int carrierFrequency=-1;

int mod_ratio = 1; //frequency of the modulator as an integer multiple of the carrier
long fm_intensity; // carries control info from updateControl to updateAudio

float smoothness = 0.95f;
Smooth <long> aSmoothIntensity(smoothness);


// FUNCTIONS

void initSynth () {
  randSeed(); // fresh random, MUST be called before startMozzi - wierd bug

  kMapCarrierFreq(0);  kMapCarrierFreq(1023);
  kMapIntensity(0);  kMapIntensity(1023);
  kMapModSpeed(0);  kMapModSpeed(1023);
  kMapEnvelopeTimes(0);  kMapEnvelopeTimes(1023);

}

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

void setCarrierFrequency (int cf) {
  carrierFrequency=cf;
}

void handleMidiNote(byte channel, byte note, byte velocity) {
  if (channel<1) channel=1;
  if (channel>=NUM_POTENTIOMETERS) channel=NUM_POTENTIOMETERS-1;
  if (channel == 1) setCarrierFrequency ((int) frequencyTable[note]);
  kEnvelope.start(envelopeLength >> attackFactors[activeKey],envelopeLength >> decayFactors[activeKey]);
}

void setFrequencies() {
    int carrier_freq;
    
    if (carrierFrequency>=0) {           // control carrier frequency via midi-in
      carrier_freq = carrierFrequency;   // get carrier frequency from last midi input (note-on)
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


void updateSynthControl(int * analogValues, bool * keys) {
  static bool lastKeys[NUM_KEYS]={1};

  freqs[0] = 1024-analogValues[0];
  freqs[1] = analogValues[1];
  freqs[2] = analogValues[2];
  
  wfs[0] = analogValues[3] >> 8;
  wfs[1] = analogValues[4] >> 8;
  wfs[2] = analogValues[5] >> 8;

  mod_ratio = (analogValues[6] >> 7) + 1;
  envelopeLength = 4500 - ( analogValues[7] << 2);

  setWavetables();
  setFrequencies();

  for (int i=0;i<NUM_KEYS;i++) {
    if ((keys[i] == 0) && (lastKeys[i] == 1)) { 

      if (i==NUM_KEYS-1) {  // mode key pressed
        actMode=0; 
        Serial.println("Continous mode enabled!");  
      } else { 
         kEnvelope.start(envelopeLength >> attackFactors[i],envelopeLength >> decayFactors[i]);
         digitalWrite(pinLeds[i],HIGH);  
         activeKey=i;
         actMode=i+1;
         Serial.print("Key ");  
         Serial.print(i+1);  
         Serial.println(" pressed!");  
      }
    }
    lastKeys[i]=keys[i];
  }

  gain = (int) kEnvelope.next(); 
  for (int i=0;i<NUM_KEYS-1;i++) {
    if (i==activeKey) analogWrite(pinLeds[i],gain*ledGainFactor); else analogWrite(pinLeds[i],0);
  }


}

int updateSynthAudio() {
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
