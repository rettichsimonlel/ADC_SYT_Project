
#include <avr/io.h>
#include <util/delay.h>

unsigned short int yes = 0;

int main()
{
  DDRB |= (1 << PB1);         //PB1 ... for LED activation
  ADMUX = 0x01;               //ADC-Input on PB2
  ADCSRA |= (1 << ADEN);      //ADC-Modul
  ADCSRB = 0x00;              //Configure free-running mode
  ADCSRA |= (1 << ADSC) | (1 << ADATE) | (1 << ADIE);   //Start ADC conversion, enable automatic triggering and enable interrupt

  while(1)
  {
    uint16_t adc_val = ADC;

    float voltage = (float) adc_val / 1024.0 * 5; //Calculate voltage
    if (voltage > 2.9) //Check the voltage
    { 
      // LED blinking
      if (yes == 0) {
        PORTB |= (1 << PB1);  //LED on
        yes = 1;
        _delay_ms(1000);
      }
      else {
        PORTB &= ~(1 << PB1); //LED off
        yes = 0;
        _delay_ms(1000);
      }
    }
    else
    {
      PORTB &= ~(1 << PB1); //LED off
      _delay_ms(5000);
    }
  }
  return 0;
}


/*
#include <avr/io.h>
#include <util/delay.h>

#define VOLTAGE_THRESHOLD 4.1

static inline void adc_setup()
{
  DDRB |= (1 << PB1);         //PB1 ... for LED activation
  ADMUX = 0x01;               //ADC-Input on PB2
  ADCSRA |= (1 << ADEN);      //ADC-Modul
  ADCSRB = 0x00;              //Configure free-running mode
  ADCSRA |= (1 << ADSC) | (1 << ADATE) | (1 << ADIE);   //Start ADC conversion, enable automatic triggering and enable interrupt
}

int main()
{
  adc_setup();

  while(1)
  {
    uint16_t adc_val = ADC;

    float voltage = ((int)adc_val >> 10) * VOLTAGE_THRESHOLD; //Calculate voltage
    if (voltage < VOLTAGE_THRESHOLD) //Check the voltage
    {
      PORTB |= (1 << PB1);  //LED on
    }
    else
    {
      // LED blinking
      static uint8_t yes = 0;
      if (yes == 0) {
        PORTB |= (1 << PB1);  //LED on
        yes = 1;
        _delay_ms(1000);
      }
      else {
        PORTB &= ~(1 << PB1); //LED off
        yes = 0;
        _delay_ms(1000);
      }
    }
  }
}
*/

/*
#include <avr/io.h>
#include <util/delay.h>

unsigned short int yes = 0;
unsigned short int voltage_below_4 = 0;

int main()
{
  DDRB |= (1 << PB1);         //PB1 ... for LED activation
  ADMUX = 0x01;               //ADC-Input on PB2
  ADCSRA |= (1 << ADEN);      //ADC-Modul
  ADCSRB = 0x00;              //Configure free-running mode
  ADCSRA |= (1 << ADSC) | (1 << ADATE) | (1 << ADIE);   //Start ADC conversion, enable automatic triggering and enable interrupt

  while(1)
  {
    uint16_t adc_val = ADC;

    float voltage = (float) adc_val / 1024.0 * 5; //Calculate voltage
    if (voltage > 4) //Check the voltage
    { 
      voltage_below_4 = 0; // reset flag when voltage is above 4V
      if (yes == 1) {
        PORTB |= (1 << PB1);  //LED on
        yes = 0;
      }
      _delay_ms(5000);
    }
    else
    {
      if (voltage_below_4 == 0) {
        // when voltage goes below 4V for the first time
        voltage_below_4 = 1; // set flag
      }
      else {
        // when voltage is below 4V and flag is set
        if (yes == 0) {
          PORTB &= ~(1 << PB1); //LED off
          yes = 1;
        }
        _delay_ms(1000);
      }
    }
  }
  return 0;
}
*/
