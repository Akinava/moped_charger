=== atmega328p
00 PC6  reset
01 PD0  BATTERY_LINE_1
02 PD1  POWER_LINE
03 PD2  BATTERY_LINE_2
07 VCC  +5v
08 GND  -5v
09 PB6  Crystal
10 PB7  Crystal
17 PB3  MOSI
18 PB4  MISO
19 PB5  SCK
20 VCC  +5v
21 AREF +5v
22 GND  -5v
27 PC4  POWER_SIGNAL
28 PC5  CHARGING_SIGNAL

=== SIGNALS
 -- (POWER_SIGNAL LED) ----- PC4
 -- (CHARGING_SIGNAL LED) -- PC5
 -- (GND_SIGNAL) ----------- GND

=== usb-asp pins

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

=== relay
                 |/--(relay[power/bat1/ba2])-(VCC 12v)
 (PD1/PD0/PD2)---|2N2222
                 |>--(GND 12v)

=== 2N222
  ___
 /___\
 |   |
 +---+
 | | |
 | | |
 E B K

 ^ ^ ^
 - p r
 1 i e
 2 n l
 v s a
     y
 v v v

=== Crystal
GND + capacitor(22pF) ----+----- OSC1
    |                  crystal(16KHz)
    + capacitor(22pF) ----+----- OSC2
