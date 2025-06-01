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

// relay
                     0-----+
(PB2/PB1/PB0)-[200Ω]-|     |-(VCC 12v)->
                     |pc817|               |/--(relay[power/bat1/ba2])-(VCC 12v)
            (GND 5v)-|     |-[10KΩ]--------|2N2222
                     +-----+               |>--(GND 12v)

// 2N222
  ___
 /___\
 |   |
 +---+
 | | |
 | | |
 E B K