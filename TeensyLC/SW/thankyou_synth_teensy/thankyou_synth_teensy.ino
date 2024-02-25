/*
   TeenSynth 
   Mozzi-based low-cost Synthesizer for Teensy-LC with Midi support!
   by Chris Veigl
   
*/

#define USE_NEOPIXEL

#include <MozziGuts.h>

#ifdef USE_NEOPIXEL
  #include <FastLED.h>
  #define NUM_LEDS 64 
  #define LED_DATAPIN 1
  #define LED_UPDATE_TIME 30
  CRGB leds[NUM_LEDS];
  void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }
  void updateLeds() { 
    static uint8_t hue = 0;
    static uint16_t actled = 0;
    static uint32_t lastLedUpdate=0;
    if (millis() - lastLedUpdate < LED_UPDATE_TIME)  return;
    lastLedUpdate = millis();  
    
    if (actled>=NUM_LEDS*2) actled=0;
    if (actled < NUM_LEDS) {
      leds[actled++] = CHSV(hue++, 255, 255);
      FastLED.show(); 
    } else { 
      leds[NUM_LEDS*2-actled++-1] = CHSV(hue++, 255, 255);
      FastLED.show();
    }
    fadeall();
  }
#endif


#include "display.h"
#include "utils.h"
#include "globals.h"
#include "synth.h"

int pinKeys[NUM_KEYS]={7,8,9,10}; 
int pinLeds[NUM_KEYS-1]={3,4,6}; 
int pinPotentiometers[NUM_POTENTIOMETERS]= {A10,A5,A3,A1,A7,A6,A4,A2}; // {A1,A2,A3,A4,A5,A6,A7,A8};
                                         

uint32_t lastDisplayUpdate=0;

int midiCCValues[NUM_POTENTIOMETERS]={0};
int analogValues[NUM_POTENTIOMETERS]={0};
int lastAnalogValues[NUM_POTENTIOMETERS]={0};
int lockAnalogValues[NUM_POTENTIOMETERS]={-1};
bool keys[NUM_KEYS]={0};


// midi note-on handler
// this maps incoming midi note-on values (per channels) to the analog potentiometer values
// and bypasses the manual potentiomenter control for a certain time
void myNoteOn(byte channel, byte note, byte velocity) {
  Serial.print("Midi Note On: Channel "); Serial.print(channel); 
  Serial.print(" note ");Serial.print(note); Serial.print(" velocity ");Serial.println(velocity);
  
  digitalWrite(PIN_INTERNAL_LED,HIGH);
                                                  
  int val=(127-note)*8; if (val<0) val=0; else if (val>1023) val=1023;

  lockAnalogValues[channel-1]=analogRead(pinPotentiometers[channel-1]);
  analogValues[channel-1]=val;
  handleMidiNote(channel, note, velocity);
}

void myNoteOff(byte channel, byte note, byte velocity){
  Serial.print("Midi Note Off: Channel "); Serial.print(channel); 
  Serial.print(" note ");Serial.print(note); Serial.print(" velocity ");Serial.println(velocity);
  digitalWrite(PIN_INTERNAL_LED,LOW);
}


void updateAnalogValues() {

  uint32_t timestamp=micros();
  for (int i=0;i<NUM_POTENTIOMETERS;i++){
    uint16_t actAnalogValue=analogRead(pinPotentiometers[i]);  // mozziAnalogRead(i); 
    if (lockAnalogValues[i]>-1) {  
      int difference=lockAnalogValues[i]-actAnalogValue;
      if (abs(difference) > ANALOG_CHANGE_THRESHOLD)  {
        lockAnalogValues[i]=-1;
        analogValues[i]=actAnalogValue;
      }
    }
    else analogValues[i]=actAnalogValue;
    
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
  #ifndef USE_NEOPIXEL          
          updateDisplayMessage(i,val);
          if (!keys[NUM_KEYS-1]) {    // if key4 is pressed: send act poti value to connected boards!
            Serial1.write((uint8_t)CMD_SET_POTI+i);
            Serial1.write((uint8_t)(analogValues[i]>>8));
            Serial1.write((uint8_t)(analogValues[i]&0xff));
          }
  #endif
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
  #ifdef USE_NEOPIXEL
    FastLED.addLeds<WS2812,LED_DATAPIN,RGB>(leds,NUM_LEDS);
    FastLED.setBrightness(84);
  #else
    Serial1.begin(115200);
  #endif

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

void checkSerialIncoming() {
#ifndef USE_NEOPIXEL  
  while (Serial1.available()) {
    uint8_t cmd=Serial1.read();
    if ((cmd&0xf0) == CMD_SET_POTI) {
      uint8_t poti=cmd&0x0f;
      uint16_t val=Serial1.read()<<8;
      val+=Serial1.read();
      Serial.print("incoming: set poti "); Serial.print(poti);
      Serial.print(" -> "); Serial.println(val);
      lockAnalogValues[poti]=analogRead(pinPotentiometers[poti]);
      analogValues[poti]=val;
    }
  }
#endif
}

void updateControl() {
  usbMIDI.read();
  updateAnalogValues();
  checkSerialIncoming();
  updateKeys();
  updateLeds();
  updateSynthControl(analogValues,keys);
  reportFreeRam();
}


int updateAudio() {
  return(updateSynthAudio());
}

void loop() {
  audioHook();
}
