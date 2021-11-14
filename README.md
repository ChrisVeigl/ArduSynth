# ArduSynth
HW/SW for low-cost Arduino-based audio synthesizers (based upon Mozzi Library).
Currently, two designs are available: one for the Arduino Nano and one for the TeensyLC microcontroller. The TeensyLC version is recommended and will be updated in the future - it offers more features like Midi control via the Teensy's usbMidi functions.

The Synthesizer sketches are based upon the "K'iin" Synthesizer by Taylan Cihan, see:
 http://digital.music.cornell.edu/taylancihan/kiin.html
 
and the "Thankyou Drone Synth" by Daniel Sinderson, see:
   https://create.arduino.cc/projecthub/scraptured/phasemod-drone-synth-w-arduino-nano-mozzi-7ab2ff 

The KICad projects (Schematics, PCB) are available in the respective HW folders, partnumbers @ digikey / Aliexpress are provided.

## Build instructions and Dependencies

* for compiling the software, the Mozzi-Library must be installed / copied to the Arduino libraries folder, see:
https://github.com/sensorium/Mozzi 
Please note that for the TeensyLC version, currently this branch must be used: https://github.com/tomcombriat/Mozzi/tree/Teensy4X
* the TeensyLC version makes use of the LC-display library: https://github.com/lexus2k/ssd1306
* in order to use the correct I2C interface for the LDC, the Wire1 interface mus be enabled either by adding -DWIRE_IMPLEMENT_WIRE1 to the teensyLC.build.flags.defs in the file Arduino\hardware\teensy\avr\boards.txt file or by uncommenting this definition in the file Arduino\hardware\teensy\avr\libraries\Wire\WireKinetis.h





