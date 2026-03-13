#include <Arduino.h>
#include <array>

constexpr int led_pin = C1;

void setup() { pinMode(led_pin, OUTPUT); }

#define FORCE_INLINE __attribute__((always_inline)) inline

FORCE_INLINE void turn_on() { GPIOC->BSHR = GPIO_Pin_1; }

FORCE_INLINE void turn_off() { GPIOC->BCR = GPIO_Pin_1; }

FORCE_INLINE void tick() { __asm__ volatile("nop"); }

template <int N> FORCE_INLINE void ticks() {
  if constexpr (N > 0) {
    tick();
    ticks<N - 1>();
  }
}

constexpr int overhead = 6;

FORCE_INLINE void send_one() {
  turn_on();
  ticks<27>();
  turn_off();
  ticks<30 - overhead>();
}

FORCE_INLINE void send_zero() {
  turn_on();
  ticks<12>();
  turn_off();
  ticks<47 - overhead>();
}

FORCE_INLINE void send_byte(uint8_t byte) {
  for (int i = 0; i < 8; i++) {
    if (byte & 0x80) {
      send_one();
    } else {
      send_zero();
    }
    byte <<= 1;
  }
}

constexpr uint8_t smooth_brightnesses[34] = {
    1,   2,   3,   5,   7,   10,  13,  16,  20,  24,  29,  34,
    39,  45,  51,  58,  65,  72,  80,  88,  97,  106, 115, 125,
    135, 146, 157, 168, 180, 192, 205, 218, 231, 245};

static uint8_t get_brightness_at_time(int32_t time, int led_i) {
  int index = (time / 64 + (led_i * 50)) % (2 * sizeof(smooth_brightnesses));
  if (index >= int(sizeof(smooth_brightnesses))) {
    index = 2 * sizeof(smooth_brightnesses) - index - 1;
  }

  return smooth_brightnesses[index];
}

void loop() {
  while (true) {
    const int32_t now = millis();
    uint8_t values[9];
    for (int i = 0; i < 9; i++) {
      values[i] = get_brightness_at_time(now, i);
    }

    delay(50);

    __disable_irq();
    send_byte(values[0]);
    send_byte(values[1]);
    send_byte(values[2]);

    send_byte(values[3]);
    send_byte(values[4]);
    send_byte(values[5]);

    send_byte(values[6]);
    send_byte(values[7]);
    send_byte(values[8]);
    __enable_irq();
  }
}
