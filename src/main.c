#include <util/delay.h>
#include "macro.h"
#include "pins.h"

# define LINE_IN 300
# define SLEEP 300
# define WAIT_LINE_SET 5000


void init_adc(void){
  // set V reference source AVCC
  UNSET(ADMUX, REFS1);
  SET(ADMUX, REFS0);

  // read bits direction
  UNSET(ADMUX, ADLAR);

  // Prescaler 128
  SET(ADCSRA, ADPS2);
  SET(ADCSRA, ADPS1);
  SET(ADCSRA, ADPS0);

  // set ADC on
  SET(ADCSRA, ADEN);
}


uint8_t check_charging_line(void){
  // set read ADC5
  UNSET(ADMUX, MUX3);
  SET(ADMUX, MUX2);
  UNSET(ADMUX, MUX1);
  SET(ADMUX, MUX0);

  // set ADC run
  SET(ADCSRA, ADSC);

  // wait
  while(CHECK_BIT(ADCSRA, ADIF));

  // return result
  if (ADC > LINE_IN){
    return 1;
  }else{
    return 0;
  }
}


uint8_t check_power_line(void){
  // set read ADC4
  UNSET(ADMUX, MUX3);
  SET(ADMUX, MUX2);
  UNSET(ADMUX, MUX1);
  UNSET(ADMUX, MUX0);

  // set ADC run
  SET(ADCSRA, ADSC);

  // wait
  while(CHECK_BIT(ADCSRA, ADIF));

  // return result
  if (ADC > LINE_IN){
    return 1;
  }else{
    return 0;
  }
}


void battery_1_on(void){
    SET_LOW(BATTERY_1_LINE_PORT, BATTERY_1_LINE_PIN);
}


void battery_1_off(void){
    SET_HIGH(BATTERY_1_LINE_PORT, BATTERY_1_LINE_PIN);
}


void battery_2_on(void){
    SET_LOW(BATTERY_2_LINE_PORT, BATTERY_2_LINE_PIN);
}


void battery_2_off(void){
    SET_HIGH(BATTERY_2_LINE_PORT, BATTERY_2_LINE_PIN);
}


void power_on(void){
    SET_HIGH(POWER_LINE_PORT, POWER_LINE_PIN);
}


void power_off(void){
    SET_LOW(POWER_LINE_PORT, POWER_LINE_PIN);
}


void init_pins(void){
    // INIT POWER_LINE
    SET_DDR_OUT(POWER_LINE_DDR, POWER_LINE_PIN);
    // INIT BATTERY_LINE_1
    SET_DDR_OUT(BATTERY_1_LINE_DDR, BATTERY_1_LINE_PIN);
    // INIT BATTERY_LINE_2
    SET_DDR_OUT(BATTERY_2_LINE_DDR, BATTERY_2_LINE_PIN);

    // INIT ADC
    init_adc();
}


void init_line(void){
    power_off();
    _delay_ms(SLEEP);
    battery_1_on();
    _delay_ms(SLEEP);
    battery_2_on();
    _delay_ms(WAIT_LINE_SET);
}


int main(void){
    _delay_ms(SLEEP);
    init_pins();
    init_line();
    _delay_ms(SLEEP);
    for (;;){
        // wait power
        while (!(check_power_line() | check_charging_line())){
            _delay_ms(SLEEP);
        }

        // set charging battery_1
        if (check_power_line()){
            power_off();
            _delay_ms(SLEEP);
            battery_1_on();
            _delay_ms(SLEEP);
            battery_2_off();
            _delay_ms(SLEEP);
            power_on();
            _delay_ms(WAIT_LINE_SET);
        }
        // wait charging battery_1
        while(check_charging_line()){
            _delay_ms(SLEEP);
        }

        _delay_ms(WAIT_LINE_SET);

        // set charging battery_2
        if (check_power_line()){
            power_off();
            _delay_ms(SLEEP);
            battery_2_on();
            _delay_ms(SLEEP);
            battery_1_off();
            _delay_ms(SLEEP);
            power_on();
            _delay_ms(WAIT_LINE_SET);
        }
        // wait charging battery_2
        while(check_charging_line()){
            _delay_ms(SLEEP);
        }

        _delay_ms(WAIT_LINE_SET);
        init_line();

        // wait till power off
        while(check_power_line()){
            _delay_ms(SLEEP);
        }
    }
}
