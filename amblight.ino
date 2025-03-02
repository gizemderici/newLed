#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUMPIXELS 12
#define DELAYVAL 10

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int BUTTON_PIN = 2;
const int POT_PIN = A0;
int potValue = 0;
int shiftOffset = 0;
uint8_t brightness;
int buttonState = 0;
int lastButtonState = LOW;

int brightnessIndex = 0;
int BRIGHTNESS_LEVELS[4] = {50, 100, 200, 255};

// Debounce için değişkenler
unsigned long lastButtonPressTime = 0;
const unsigned long BUTTON_DEBOUNCE_DELAY = 200;  // 200 ms gecikme

struct NeoPixel {
  int red;
  int green;
  int blue;
};

NeoPixel leds[NUMPIXELS];

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pinMode(BUTTON_PIN, INPUT);
  brightness = BRIGHTNESS_LEVELS[brightnessIndex];
}

void loop() {
  // Buton okuma
  int buttonReading = digitalRead(BUTTON_PIN);
  
  // Butonun mekanik titreşimlerini önlemek için debounce kontrolü
  if (buttonReading == HIGH && lastButtonState == LOW && (millis() - lastButtonPressTime) > BUTTON_DEBOUNCE_DELAY) {
    lastButtonPressTime = millis();
    brightnessIndex++;
    
    if (brightnessIndex > 3) {
      brightnessIndex = 0;
    }
    
    brightness = BRIGHTNESS_LEVELS[brightnessIndex];
    pixels.setBrightness(brightness);
  }
  
  lastButtonState = buttonReading;

  // Potansiyometre okuma
  potValue = analogRead(POT_PIN);
  shiftOffset = map(potValue, 0, 1023, 0, NUMPIXELS + 1);
  
  if (Serial.available() >= NUMPIXELS * 3) {
    for (int i = 0; i < NUMPIXELS; i++) {
      leds[i].red = Serial.read();
      leds[i].green = Serial.read();
      leds[i].blue = Serial.read();
    }
  }

  // Kaydırma işlemi
  for (int i = 0; i < NUMPIXELS; i++) {
    int shiftedIndex = (i + shiftOffset) % NUMPIXELS;
    pixels.setPixelColor(shiftedIndex, pixels.Color(leds[i].red, leds[i].green, leds[i].blue));
  }

  pixels.show();
  delay(DELAYVAL);
}
