#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

constexpr int data_pin = 3;
constexpr int led_num = 3;

Adafruit_NeoPixel pixels(led_num, data_pin, NEO_RGB + NEO_KHZ800);

void setup() { pixels.begin(); }

static void set_brightnesses(const uint8_t b1, const uint8_t b2,
                             const uint8_t b3, const uint8_t b4,
                             const uint8_t b5, const uint8_t b6,
                             const int delay_ms) {
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(b1, b2, b3));
  pixels.setPixelColor(1, pixels.Color(b4, b5, b6));
  pixels.show();
  delay(delay_ms);
}

void loop() {
  set_brightnesses(255, 0, 0, 0, 0, 0, 300);
  set_brightnesses(0, 255, 0, 0, 0, 0, 300);
  set_brightnesses(0, 0, 255, 0, 0, 0, 300);
  set_brightnesses(0, 0, 0, 255, 0, 0, 300);
  set_brightnesses(0, 0, 0, 0, 255, 0, 300);
  set_brightnesses(0, 0, 0, 0, 0, 255, 300);
  set_brightnesses(0, 0, 0, 0, 255, 255, 300);
  set_brightnesses(0, 0, 0, 255, 255, 255, 300);
  set_brightnesses(0, 0, 255, 255, 255, 255, 300);
  set_brightnesses(0, 255, 255, 255, 255, 255, 300);
  set_brightnesses(255, 255, 255, 255, 255, 255, 300);
  set_brightnesses(255, 255, 255, 255, 255, 0, 300);
  set_brightnesses(255, 255, 255, 255, 0, 0, 300);
  set_brightnesses(255, 255, 255, 0, 0, 0, 300);
  set_brightnesses(255, 255, 0, 0, 0, 0, 300);
  set_brightnesses(255, 0, 0, 0, 0, 0, 300);
  set_brightnesses(0, 0, 0, 0, 0, 0, 300);
}
