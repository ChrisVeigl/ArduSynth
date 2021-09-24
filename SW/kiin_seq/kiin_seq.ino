//
// based upon K'iin Synthesizer by Taylan Cihan
// http://digital.music.cornell.edu/taylancihan/kiin.html
//
// modified for FuzzyK'iin PCB by Chris Veigl
//


// 
// ---- INITIALS ----
//


#include <MozziGuts.h>
#include <WavePacket.h>
#include <RollingAverage.h>
#include <AutoMap.h>
#include <EventDelay.h>
#include <mozzi_rand.h>
#include <EEPROM.h>

#define DEBUG_OUTPUT 1
#define CONTROL_RATE 64

WavePacket <DOUBLE> wavey; // DOUBLE selects 2 overlapping streams
EventDelay kEventDelay;
int bitR = 8;
int krModSpd = 2;
int counter = 0;



// 
// ---- ANALOG INPUTS ----
//
const int KNOB1_PIN = 0; // oscillator freq
const int KNOB2_PIN = 1; // filter q
const int KNOB3_PIN = 2; // filter freq
const int KNOB4_PIN = 3; // control speed
const int KNOB5_PIN = 4; // playback mode
const int KNOB6_PIN = 5; // bit rate
const int KNOB7_PIN = 6; // arpeggio speed
const int KNOB8_PIN = 7; // sequencer speed



// 
// ---- AUTOMAPS ----
//
AutoMap kMapF(0, 1023, 5, 100); // oscillator freq (knob 1)
AutoMap kMapFT(5, 100, 0, 12); // oscillator tuning-array index (knob 1)
AutoMap kMapTuneArrSel(4, 64, 0, 5); // oscillator tuning-array index (knob 4)
AutoMap kMapBw(0, 1023, 1, 1000); // filter q (knob 2)
AutoMap kMapCf(0, 1023, 60, 2000); // filter freq (knob 3)
AutoMap kMapArrL(0, 1023, 4, 64); // control speed for random from array (mode3&4, knob 4)
AutoMap kMapMode(0, 1023, 0, 5); // mode (knob 5)
AutoMap kMapBit(0, 1023, 1, 7); // bit rate (knob 6)
AutoMap kMapModSpd(0, 1023, 1, 40); // modulation speed (knob 7)
AutoMap kMapModArrL(4, 64, 4, 40); // modulation array length (knob 4)



// 
// ---- ARRAYS ----
//
int arr[] = { 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
float tuneArr[6][13] = {
  { 1, 1.285, 1.5, 1.75, 2, 2.25, 2.57, 2.8, 3, 3.11, 3.5, 3.857, 4 }, // overtone series
  { 1, 1.166, 1.33, 1.5, 1.75, 2, 2.332, 2.66, 3.0, 3.5, 4, 4.664, 6 }, // pentatonic
  { 1, 1.166, 1.5, 2, 2.33, 3.0, 4, 4.66, 6.0, 8, 9.33, 12, 16 }, // minor arpeggio
  { 1, 1.25, 1.5, 2, 2.5, 3.0, 4, 5.0, 6.0, 8, 10, 12, 16 }, // major arpeggio
  { 1, 1.25, 1.56, 2, 2.5, 3.12, 4, 5.0, 6.24, 8, 10, 12.48, 16 }, // augmented arpeggio
  { 1, 1.071, 1.25, 1.33, 1.5, 1.56, 1.890, 2.0, 2.142, 2.5, 2.66, 3.0, 3.12 } // hicaz
};
int stepModArr[] = { 25, 50, 75, 100, 150, 200, 300, 400, 800, 1600, 2400, 3000, 2400, 1200, 800, 400, 300, 150, 75, 50 };

#define KNOBS 7
#define SEQ_STEPS 3

#define BUTTON_REC 11
#define BUTTONS_STEP 3
#define LEDS_STEP 6

#define MIN_POTI_MOVEMENT 5
#define POTI_LIVE_VALUE 1025

#define STORE_BYPASS_TIME  64
#define SELECT_BYPASS_TIME 10

#define MAGIC_BYTE 123

uint16_t storedPositions[SEQ_STEPS][KNOBS]={512};
uint16_t actPosition[KNOBS];
uint16_t holdPosition[KNOBS]={POTI_LIVE_VALUE};
uint8_t  actStep=0;
uint8_t  storing=0;
uint16_t bypass_button=0;
uint16_t seq_counter=0;
uint16_t  initParameters=10;


// 
// ---- SETUP ----
//
void setup() {
  Serial.begin(115200);
  Serial.println ("  ********* Welcome to Kiin Synth/ Sequencer  *************");
  randSeed();

  pinMode (BUTTON_REC, INPUT_PULLUP);
  pinMode (BUTTONS_STEP, INPUT_PULLUP);
  pinMode (BUTTONS_STEP+1, INPUT_PULLUP);
  pinMode (BUTTONS_STEP+2, INPUT_PULLUP);

  pinMode (LEDS_STEP, OUTPUT);
  pinMode (LEDS_STEP+1, OUTPUT);
  pinMode (LEDS_STEP+2, OUTPUT);

  if (EEPROM.read (0) == MAGIC_BYTE)  {
     EEPROM.get (1,storedPositions);
    // EEPROM.get (50,wavey);
  }

  memcpy (actPosition,storedPositions[actStep],sizeof(actPosition));
  
  delay(200);
  startMozzi(CONTROL_RATE);
  for (uint8_t z=0;z<KNOBS;z++) holdPosition[z]=1024-mozziAnalogRead(z);  // hold current poti positions!      

}


void getSequence(uint8_t seq) {
    digitalWrite (actStep+LEDS_STEP,LOW);
    actStep=seq;
    digitalWrite(actStep+LEDS_STEP,HIGH);
    memcpy (actPosition,storedPositions[actStep],sizeof(actPosition));
    for (uint8_t z=0;z<KNOBS;z++) holdPosition[z]=1024-mozziAnalogRead(z);  // hold current poti positions!      
    if (DEBUG_OUTPUT) {
      Serial.print ("RECALLING STEP "); Serial.println (actStep);
      for (int i=0; i<KNOBS; i++) {
        Serial.print ("Knob "); Serial.print (i+1); Serial.print (": "); Serial.print (actPosition[i]); 
        Serial.print (" - Poti locked at "); Serial.println (holdPosition[i]); 
      }      
    }
}




// 
// ---- CONTROL ----
//
void updateControl() { 

  if (initParameters) {
    for (int i=0;i<KNOBS;i++) {
      actPosition[i]=rand(1023); 
    }
    initParameters--;
    if (initParameters == 0) getSequence(0);
  }

  if (( digitalRead (BUTTON_REC) == LOW) && (!storing)) {  // rec pressed: store parameters of current sequence slot
    storing = STORE_BYPASS_TIME;
    memcpy (storedPositions[actStep],actPosition,sizeof(actPosition));
    EEPROM.update (0,MAGIC_BYTE);
    EEPROM.put (1,storedPositions);
  //  EEPROM.put (50,wavey);

    if (DEBUG_OUTPUT) {
      Serial.print ("STORING STEP "); Serial.println (actStep);
      for (int i=0; i<KNOBS; i++) {
        Serial.print ("Knob "); Serial.print (i+1); Serial.print (": "); Serial.println (storedPositions[actStep][i]); 
      }
    }
  }

  if (storing) {  // blink led of current sequence slot when storing 
    if (storing & 8) digitalWrite (actStep+LEDS_STEP,HIGH); else digitalWrite (actStep+LEDS_STEP,LOW);
    if (!(--storing)) digitalWrite (actStep+LEDS_STEP,HIGH);
  }

  uint16_t seq_speed =1024-mozziAnalogRead(KNOB8_PIN);  // sequencing speed 
  if (seq_speed > 10) {
    seq_speed-=10;
    seq_counter++;
    if (seq_counter > 130-(seq_speed >> 3)) {
      seq_counter=0;
      getSequence((actStep+1) % SEQ_STEPS);  // perform automatic slot change
    }
  }

  for (uint8_t i=0;i<SEQ_STEPS; i++) {
    if ((digitalRead (BUTTONS_STEP+i) == LOW) && (!bypass_button)) {  // step button was pressed: manual slot change
      bypass_button=SELECT_BYPASS_TIME;
      getSequence(i);
    }
  }

  if (bypass_button) bypass_button--;
  
  for (uint8_t i=0;i<KNOBS;i++) {
    uint16_t currentPotiValue=1024-mozziAnalogRead(i);

    if (!initParameters) {
      if (holdPosition[i]==POTI_LIVE_VALUE) {
        actPosition[i]=currentPotiValue;
      } 
      else {  // use stored parameter position!
        int delta=holdPosition[i]-currentPotiValue;
        if (( delta > MIN_POTI_MOVEMENT ) || (delta < -MIN_POTI_MOVEMENT)) {
          holdPosition[i]=POTI_LIVE_VALUE;  // allow LIVE_VALUES if poti was moved!
          if (DEBUG_OUTPUT) {
            Serial.print ("unlock Knob "); Serial.print (i+1); Serial.print (" delta="); Serial.println (delta);
          }
        }
      }
    } 
    //else initParameters=0; 
  }
  
  // mod Spd
  krModSpd = actPosition[KNOB7_PIN];
  krModSpd = kMapModSpd(krModSpd);
  kEventDelay.set(krModSpd);
  
  // bit rate
  bitR = actPosition[KNOB6_PIN];
  bitR = kMapBit(bitR);
  
  // mode
  int mode = actPosition[KNOB5_PIN];
  mode = kMapMode(mode);
  
  // array length
  int arrMax = actPosition[KNOB4_PIN];
  arrMax = kMapArrL(arrMax);
  
  // synth properties
  float fundamental = actPosition[KNOB1_PIN]+1;
  float bandwidth = actPosition[KNOB2_PIN];
  float centre_freq = actPosition[KNOB3_PIN];
  
  
  // OPERATION  
  // knob values
  if (mode == 0) 
  {
    fundamental = kMapF(fundamental);
    bandwidth = kMapBw(bandwidth);
    centre_freq = kMapCf(centre_freq);
    wavey.set(fundamental, bandwidth, centre_freq);
  }
  
  
  // scales
  else if (mode == 1)
  {
    int tuneArrSel;
    int tunArrI;
    tuneArrSel = kMapTuneArrSel(arrMax); // select which array for tuning
    fundamental = kMapF(fundamental); // map fundamental
    tunArrI = kMapFT(fundamental); // tuning array index
    fundamental = tuneArr[tuneArrSel][tunArrI] * 44; // tune fundamental
    bandwidth = kMapBw(bandwidth);
    centre_freq = kMapCf(centre_freq);
    wavey.set(fundamental, bandwidth, centre_freq);
  }
  
  
  // randomize fundamental frequency from array
  else if (mode == 2)
  {
    if (arr[rand(arrMax)] == 2)
    {
      int randFreq = rand(5, 100);
      fundamental = kMapF(fundamental);
      fundamental = fundamental + randFreq;
    }
    bandwidth = kMapBw(bandwidth);
    centre_freq = kMapCf(centre_freq); 
    wavey.set(fundamental, bandwidth, centre_freq);
  }
  
  
  // randomize all values from array
  else if (mode == 3)
  {
    int f = arr[rand(arrMax)]; // frequency
    int b = arr[rand(arrMax)]; // bandwidth
    int c = arr[rand(arrMax)]; // center freq
    if (f == 2)
    {
      int rFq = rand(5, 100);
      fundamental = kMapF(fundamental);
      fundamental = fundamental + rFq;
    }
    if (b == 2)
    {
      int rBW = rand(100, 1000);
      bandwidth = kMapBw(bandwidth);
      bandwidth = bandwidth + rBW;
    }
    if (c == 2)
    {
      int rCF = rand(1000, 2500); 
      centre_freq = kMapCf(centre_freq); 
      centre_freq = centre_freq + rCF;
    } 
    wavey.set(fundamental, bandwidth, centre_freq);
  }
  
  
  // randomize all values
  else if (mode == 4)
  {
    int rF = arrMax + 1; // how much random
    fundamental = kMapF(fundamental);
    bandwidth = kMapBw(bandwidth);
    centre_freq = kMapCf(centre_freq); 
    fundamental = fundamental + rand(rF*3);
    bandwidth = bandwidth + rand(rF*25);
    centre_freq = centre_freq + rand(rF*10, rF*40);
    wavey.set(fundamental, bandwidth, centre_freq);
  }
  
  
  // arpeggio
  else if (mode == 5)
  {
    if (kEventDelay.ready()) 
    {
      int stepModLenth = kMapModArrL(arrMax);
      counter++;
      if (counter >= stepModLenth) { counter = 0; }    
      kEventDelay.start();
      fundamental = fundamental + stepModArr[counter];
      bandwidth = kMapBw(bandwidth);
      centre_freq = kMapCf(centre_freq);
      wavey.set(fundamental, bandwidth, centre_freq);
      if (DEBUG_OUTPUT) Serial.println(counter);
    }
  }  
  
}



// 
// ---- AUDIO ----
//
int updateAudio() {
  return wavey.next()>>bitR;
}



// 
// ---- LOOP ----
//
void loop() {
  audioHook(); // required here
}
