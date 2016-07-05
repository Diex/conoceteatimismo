#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

byte sample = 0;
boolean sample_waiting = false;
byte current_bit = 0;
byte result = 0;

void setup() {
  Serial.begin(115200);
  wdtSetup();
}

void loop()
{
  if (sample_waiting) {
    sample_waiting = false;

    result = rotl(result, 1); // Spread randomness around
    result ^= sample; // XOR preserves randomness

    current_bit++;
    if (current_bit > 7)
    {
      current_bit = 0;
      Serial.write(result); // raw binary
    }
  }
}

// Rotate bits to the left
// https://en.wikipedia.org/wiki/Circular_shift#Implementing_circular_shifts
byte rotl(const byte value, int shift) {
  if ((shift &= sizeof(value)*8 - 1) == 0)
    return value;
  return (value << shift) | (value >> (sizeof(value)*8 - shift));
}

// Setup of the watchdog timer.
void wdtSetup() {
  cli();
  MCUSR = 0;
  
  /* Start timed sequence */
  WDTCSR |= _BV(WDCE) | _BV(WDE);

  /* Put WDT into interrupt mode */
  /* Set shortest prescaler(time-out) value = 2048 cycles (~16 ms) */
  WDTCSR = _BV(WDIE);

  sei();
}

// Watchdog Timer Interrupt Service Routine
ISR(WDT_vect)
{
  sample = TCNT1L; // Ignore higher bits
  sample_waiting = true;
}
