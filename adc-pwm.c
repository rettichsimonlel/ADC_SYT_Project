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

    float voltage = (float) adc_val / 1023.0 * 4.1; //Calculate voltage
    if (voltage < 4) //Check the voltage
    {
      PORTB |= (1 << PB1);  //LED on
    }
    else
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
