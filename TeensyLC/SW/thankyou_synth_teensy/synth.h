


#ifndef _SYNTH_H_
#define _SYNTH_H_


void initSynth ();
void updateSynthControl(int * analogValues, bool * keys);
void handleMidiNote(byte channel, byte note, byte velocity);
void setCarrierFrequency (int cf);
int updateSynthAudio();

#endif
