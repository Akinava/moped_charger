#ifndef MACRO_H
#define MACRO_H

// Bit
#define CHECK_BIT(BYTE, BIT) !(BYTE & _BV(BIT))
#define UNSET(BYTE, BIT) BYTE &= ~_BV(BIT)
#define SET(BYTE, BIT) BYTE |= _BV(BIT)

// DDR Data Direction Register
#define SET_DDR_OUT(DDR, PIN) DDR |= _BV(PIN)
#define SET_DDR_IN(DDR, PIN) DDR &= ~_BV(PIN)
#define SET_PULLUP(PORTS, PIN) PORTS |= _BV(PIN)

// PORTS Data Register
#define SET_HIGH(PORTS, PIN) PORTS |= _BV(PIN)
#define SET_LOW(PORTS, PIN) PORTS &= ~_BV(PIN)

// PINS Input Pins Register
#define CHECK_PIN(PINS, PIN) !(PINS & _BV(PIN))

#endif
