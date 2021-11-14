/*
   TeenSynth 
   Mozzi-based low-cost Synthesizer for Teensy-LC with Midi support!
   by Chris Veigl
   
*/


#include <MozziGuts.h>


#include "display.h"
#include "utils.h"
#include "globals.h"
#include "synth.h"

int pinKeys[NUM_KEYS]={7,8,9,10}; 
int pinLeds[NUM_KEYS-1]={3,4,6}; 
int pinPotentiometers[NUM_POTENTIOMETERS]={A1,A2,A3,A4,A5,A6,A7,A8};

int bypassManualControl=0;
uint32_t lastDisplayUpdate=0;

int midiCCValues[NUM_POTENTIOMETERS]={0};
int analogValues[NUM_POTENTIOMETERS]={0};
int lastAnalogValues[NUM_POTENTIOMETERS]={0};
bool keys[NUM_KEYS]={0};


// midi note-on handler
// this maps incoming midi note-on values (per channels) to the analog potentiometer values
// and bypasses the manual potentiomenter control for a certain time
void myNoteOn(byte channel, byte note, byte velocity) {
  Serial.print("Midi Note On: Channel "); Serial.print(channel); 
  Serial.print(" note ");Serial.print(note); Serial.print(" velocity ");Serial.println(velocity);
  
  digitalWrite(PIN_INTERNAL_LED,HIGH);
  
  bypassManualControl=BYPASS_MANUAL_CONTROL_TIME;  // currently, midi in bypasses all manual controls for a certain time
                                                   // TBD: improve this concept ...
  int val=(127-note)*8; if (val<0) val=0; else if (val>1023) val=1023;
  analogValues[channel-1]=val;
  handleMidiNote(channel, note, velocity);
}

void myNoteOff(byte channel, byte note, byte velocity){
  Serial.print("Midi Note Off: Channel "); Serial.print(channel); 
  Serial.print(" note ");Serial.print(note); Serial.print(" velocity ");Serial.println(velocity);
  digitalWrite(PIN_INTERNAL_LED,LOW);
}


void updateAnalogValues() {
  if (bypassManualControl) { 
    bypassManualControl--;
    if (! bypassManualControl) 
      setCarrierFrequency (-1);  // disable midi-controlled carrier frequency
    return; 
  }
  uint32_t timestamp=micros();
  for (int i=0;i<NUM_POTENTIOMETERS;i++){
    analogValues[i]=analogRead(pinPotentiometers[i]);  // mozziAnalogRead(i); 
    int difference=lastAnalogValues[i]-analogValues[i];
    if (abs(difference) > ANALOG_CHANGE_THRESHOLD) {
            
      int val=map(analogValues[i],0,1024,0,127);
      if (val != midiCCValues[i]) {        
        midiCCValues[i]=val;
        lastAnalogValues[i]=analogValues[i];
        // Serial.print("Send CC ");Serial.print(i);Serial.print(" -> ");Serial.println(val);
        usbMIDI.sendControlChange(i, val, MIDI_CHANNEL);

        if (millis() - lastDisplayUpdate > DISPLAY_UPDATE_TIME)  {
          lastDisplayUpdate = millis();
          updateDisplayMessage(i,val);
        }
      }
    }
  }
  // Serial.print("Time=");Serial.println(micros()-timestamp); 
}

void updateKeys() {
  for (int i=0;i<NUM_KEYS;i++) {
    keys[i] = digitalRead(pinKeys[i]);
  }
}


void setup() {
  delay (200);
  Serial.begin(9600);

  pinMode(PIN_INTERNAL_LED, OUTPUT);
  for (int i=0;i<NUM_KEYS;i++) 
    pinMode(pinKeys[i], INPUT_PULLUP);
  for (int i=0;i<NUM_KEYS-1;i++) 
    pinMode(pinLeds[i], OUTPUT);

  initSynth();
  initDisplay();

  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);

  Serial.println("TeensySynth welcome!");
  Serial.print("Control Rate = ");  Serial.println(CONTROL_RATE);

  startMozzi(CONTROL_RATE);  
}


void updateControl() {

  usbMIDI.read();
  updateAnalogValues();
  updateKeys();
  updateSynthControl(analogValues,keys);
  reportFreeRam();
 
}


int updateAudio() {
  return(updateSynthAudio());
}

void loop() {
  audioHook();
}
