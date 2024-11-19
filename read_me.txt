// usb-asp pins

  GGGGV
  nnnnc
  ddddc
  |||||
 +-----+
 |08642|
 |97531|
 +-+ +-+
   +-+
  |||||
  MSR M
  ICS O
  SKT S
  O   I

// ATtiny85 SPI

       0----+
-(RST)-|    |-(VCC)--
      -|    |-(CSK)--
      -|    |-(MISO)-
-(GND)-|    |-(MOSI)-
       +----+

// pins          Attiny 85
               0----------+
----(RST)------+ PB5  Vcc +---(+)-------
-(POWER_CHECK)-+ PB3  PB2 +(POWER_RELAY)-
-(FAN_CHECK)---+ PB4  PB1 +(BAT_1_RELAY)-
------(-)------+ GND  PB0 +(BAT_2_RELAY)-
               +----------+