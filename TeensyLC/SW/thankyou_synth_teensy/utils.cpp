#include <Arduino.h>

extern "C" char* sbrk(int incr);
int freeRam() {
  char top;
  return &top - reinterpret_cast<char*>(sbrk(0));
}

void reportFreeRam() { 
  static uint32_t  reporttime=0;
  uint32_t time = millis();
  if((time - reporttime) > 2000) {
    Serial.print("Free RAM=");
    Serial.println(freeRam());
    reporttime=time;
  }
}
