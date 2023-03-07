#include<avr/io.h>

void adc_setup()
{
  DDRB |= (1 << PB1);         //PB1 as output to activate LED
  ADCSRA |= (1 << ADEN);      //Enable ADC module
  ADMUX = 0x01; // configuring PB2 to take input
  ADCSRB = 0x00;           //Configuring free running mode
  ADCSRA |= (1 << ADSC) | (1 << ADATE);   //Start ADC conversion and enabling Auto trigger
}

int main()
{
  adc_setup();
  while(1)
  {
    int adc_l = ADCL; //value of Input  Voltage in lower register
    int adc_val = (ADCH << 8) | adc_l;   //Reading ADCH and coimbining the data
    if (adc_val >= 510 && adc_val <= 520) //Lights up the LED under certain voltage 2.25 to 2.3 level
    { 
      PORTB |= (1 << PB1);  //LED remain ON
    }

    else        //blink condition 
    {
      PORTB &= ~(1 << PB1); //LED toggle
    }
    ADCSRA |= (1 << ADIF);
  }
}
