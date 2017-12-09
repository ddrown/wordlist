#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <wordlist.h>

// expects an SSD1306 128x64 display on the default i2c bus, address 0x3C
// on the STM32F103C8, that is PB6/PB7
// don't forget to comment out SSD1306_128_32 and uncomment SSD1306_128_64 in Adafruit_SSD1306.h
// no reset pin is used
// display will show 6 lines of 2 words each as fast as possible

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

wordlist w;

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  w.start_walk();
}

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  for(uint8_t i = 0; i < 6; i++) {
    addwords();
  }
  display.display();
}

void addwords() {
  const char *nextword;
  for(uint8_t i = 0; i < 2; i++) {
    nextword = w.next_word();
    if(nextword == NULL) {
      w.start_walk();
      return;
    }
    display.print(nextword);
    display.print(" ");
  }
  display.println("");
}
