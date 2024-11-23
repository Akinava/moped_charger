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

// relay
                     0-----+
(PB2/PB1/PB0)-[200Ω]-|     |-(VCC 12v)->
                     |pc817|               |/--(relay[power/bat1/ba2])-(VCC 12v)
            (GND 5v)-|     |-[10KΩ]--------|2N2222
                     +-----+               |>--(GND 12v)

// FAN CHECK
                     0-----+
(FAN VCC 12v)-[10KΩ]-|     |-[200Ω]-(VCC 5v)
                     |pc817|
       (FAN GND 12v)-|     |-(PB2)
                     +-----+

// POWER CHECK

(VCC 68v)--[47KΩ]-+
                  |  0-----+
          +[10KΩ]-+--|     |-[200Ω]-(VCC 5v)
          |          |pc817|
(GND 68v)-+----------|     |-(PB3)
                     +-----+

// 2N222
  ___
 /___\
 |   |
 +---+
 | | |
 | | |
 E B K