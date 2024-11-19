#define F_CPU 1000000UL

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

// DDR Data Direction Register
#define SET_DDR_OUT(DDR, PIN) DDR |= _BV(PIN)
#define SET_DDR_IN(DDR, PIN) DDR &= ~ _BV(PIN)
#define SET_PULLUP(PORTS, PIN) PORTS |= _BV(PIN)

// PORTS Data Register
#define SET_HIGH(PORTS, PIN) PORTS |= _BV(PIN)
#define SET_LOW(PORTS, PIN) PORTS &= ~ _BV(PIN)

// PINS Input Pins Register
#define CHECK_PIN(PINS, PIN) !(PINS & _BV(PIN))

// DEFINE POWER_CHECK
#define POWER_CHECK_DDR DDRB
#define POWER_CHECK_PORT PORTB
#define POWER_CHECK_PINS PINB
#define POWER_CHECK_PIN PB3

// DEFINE FAN_CHECK
#define FAN_CHECK_DDR DDRB
#define FAN_CHECK_PORT PORTB
#define FAN_CHECK_PINS PINB
#define FAN_CHECK_PIN PB4

// DEFINE POWER_RELAY
#define POWER_RELAY_DDR DDRB
#define POWER_RELAY_PORT PORTB
#define POWER_RELAY_PIN PB2

// DEFINE BAT_1_RELAY
#define BAT_1_RELAY_DDR DDRB
#define BAT_1_RELAY_PORT PORTB
#define BAT_1_RELAY_PIN PB1

// DEFINE BAT_2_RELAY
#define BAT_2_RELAY_DDR DDRB
#define BAT_2_RELAY_PORT PORTB
#define BAT_2_RELAY_PIN PB0

void power_on(void){
    SET_HIGH(POWER_RELAY_PORT, POWER_RELAY_PIN);
}

void power_off(void){
    SET_LOW(POWER_RELAY_PORT, POWER_RELAY_PIN);
}

void bat_1_on(void){
    SET_LOW(BAT_1_RELAY_PORT, BAT_1_RELAY_PIN);
}

void bat_1_off(void){
    SET_HIGH(BAT_1_RELAY_PORT, BAT_1_RELAY_PIN);
}

void bat_2_on(void){
    SET_LOW(BAT_2_RELAY_PORT, BAT_2_RELAY_PIN);
}

void bat_2_off(void){
    SET_HIGH(BAT_2_RELAY_PORT, BAT_2_RELAY_PIN);
}

void init_pins(void){
    SET_DDR_IN(POWER_CHECK_DDR, POWER_CHECK_PIN);
    SET_PULLUP(POWER_CHECK_PORT, POWER_CHECK_PIN);

    SET_DDR_IN(FAN_CHECK_DDR, FAN_CHECK_PIN);
    SET_PULLUP(FAN_CHECK_PORT, FAN_CHECK_PIN);

    SET_DDR_OUT(POWER_RELAY_DDR, POWER_RELAY_PIN);
    SET_DDR_OUT(BAT_1_RELAY_DDR, BAT_1_RELAY_PIN);
    SET_DDR_OUT(BAT_2_RELAY_DDR, BAT_2_RELAY_PIN);

    power_off();
    bat_1_on();
    bat_2_on();
}

void soft_reset_power(void){
    power_off();
    _delay_ms(3000);
    bat_1_on();
    _delay_ms(3000);
    bat_2_on();
}

void charge(void){
    if(!CHECK_PIN(POWER_CHECK_PINS, POWER_CHECK_PIN)){return;}

    bat_2_off();
    _delay_ms(3000);
    power_on();
    _delay_ms(3000);
    while(CHECK_PIN(FAN_CHECK_PINS, FAN_CHECK_PIN)){_delay_ms(100);}

    if(!CHECK_PIN(POWER_CHECK_PINS, POWER_CHECK_PIN)){
        soft_reset_power();
        return;
    }

    bat_1_off();
    _delay_ms(3000);
    bat_2_on();
    _delay_ms(3000);
    while(CHECK_PIN(FAN_CHECK_PINS, FAN_CHECK_PIN)){_delay_ms(100);}

    soft_reset_power();

    while(CHECK_PIN(POWER_CHECK_PINS, POWER_CHECK_PIN)){_delay_ms(100);}
}

int main(void){
    _delay_ms(100);
    init_pins();
    for (;;){
        charge();
        _delay_ms(100);
    }
}
