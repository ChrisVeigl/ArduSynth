
#include <Adafruit_GFX.h>
#include "src/Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//   using 1MHz I2C clock frequency
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET,1000000,1000000);

char msg[20];


void initDisplay (void) {
  if(!display.begin( SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }

  display.clearDisplay();
  display.display();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(10,10);             // Start at top-left corner
  display.print("TeenSynth");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  delay(200);

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    display.fillTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_INVERSE);
    display.display();
    delay(1);
  }
  display.display();
  delay(2000);

}


void updateDisplayMessage(uint8_t chn, uint16_t val) {
  sprintf(msg,"CC%d->%d",chn+1,val); 
  display.clearDisplay();
  display.setCursor(5,10);
  display.print(msg);
  display.display();
}        
