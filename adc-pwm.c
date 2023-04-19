#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

bool yes = false;

void adc_setup()
{
  DDRB |= (1 << PB1);         //PB1 ... for LED activation
  ADCSRA |= (1 << ADEN);      //ADC-Modul
  ADMUX = 0x01;               //ADC-Input on PB2
  ADCSRB = 0x00;              //Configure free-running mode
  ADCSRA |= (1 << ADSC) | (1 << ADATE) | (1 << ADIE);   //Start ADC conversion, enable automatic triggering and enable interrupt
}

int main()
{
  adc_setup();

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
      if (yes == false) {
        PORTB |= (1 << PB1);  //LED on
        yes = true;
        _delay_ms(1000);
      }
      else {
        PORTB &= ~(1 << PB1); //LED off
        yes = false;
        _delay_ms(1000);
      }
    }
  }
}
