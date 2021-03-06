# ArduSynth
HW/SW for low-cost Arduino-based audio synthesizers, using the Mozzi Library.
Currently, two designs are available: one for the Arduino Nano and one for the TeensyLC microcontroller. The TeensyLC version is recommended and will be updated in the future - it offers more features like Midi control via the Teensy's usbMidi functions.
The KICad projects (Schematics, PCB) are available in the respective HW folders, partnumbers @ digikey / Aliexpress are provided.

## About the demo Synth Sketches

Synthesizer sketches can be added / modified on demand. Currently there are two demo synth designs available, based upon:

* the "K'iin" Synthesizer by Taylan Cihan, see: http://digital.music.cornell.edu/taylancihan/kiin.html
 
* the "Thankyou Drone Synth" by Daniel Sinderson, see:
   https://create.arduino.cc/projecthub/scraptured/phasemod-drone-synth-w-arduino-nano-mozzi-7ab2ff 


## SW-Build instructions and Dependencies

* for compiling the software, the Mozzi-Library must be installed / copied to the Arduino libraries folder, see:
https://github.com/sensorium/Mozzi 

For the TeensyLC version, follwing alternative/additional libraries are used:
* currently this branch of the Mozzi library is needed for TeensyLC support: https://github.com/tomcombriat/Mozzi/tree/Teensy4X
* the Adafruit library for the SSD1306 OLed-Display is used: https://github.com/adafruit/Adafruit_SSD1306 
Please note that a modified version of this library is delivered in the src folder - the display method was adapted in order to call audioHook() - which prevents distorted audio during display updates.
* furthermore, the Adafruit GFX library https://github.com/adafruit/Adafruit-GFX-Library and the Adafruit BUI-IO library https://github.com/adafruit/Adafruit_BusIO are needed - they can be installed from the Arduinos Library manager.
* in order to use the correct I2C interface of the TeensyLC, the Wire1 interface must be enabled either by adding "-DWIRE_IMPLEMENT_WIRE1" to the teensyLC.build.flags.defs in the file Arduino\hardware\teensy\avr\boards.txt file or by uncommenting line 43 in file Arduino\hardware\teensy\avr\libraries\Wire\WireKinetis.h





