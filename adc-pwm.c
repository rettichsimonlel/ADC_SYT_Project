/*
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
*/

/*
#include <avr/io.h>

#define LED_PIN PB2 // LED connected to PB0

void ADC_init(void) {
  // Configure ADC reference voltage
  ADMUX |= (1 << REFS0); // use AVCC as reference voltage
  
  // Configure ADC prescaler
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // set prescaler to 128
  
  // Configure ADC input channel
  ADMUX |= (1 << MUX0); // use ADC1 as input channel
  
  // Enable ADC
  ADCSRA |= (1 << ADEN);
}

uint16_t ADC_read(void) {
  // Start ADC conversion
  ADCSRA |= (1 << ADSC);
  
  // Wait for conversion to complete
  while (ADCSRA & (1 << ADSC));
  
  // Return ADC result
  return ADC;
}

int main(void) {
  // Initialize ADC
  ADC_init();
  
  // Configure LED pin as output
  DDRB |= (1 << LED_PIN);
  
  while (1) {
    // Read ADC value
    uint16_t adc_value = ADC_read();
    
    // Check if voltage is below 3V
    if (adc_value < 819) { // 614 = 3V * 1024 / 5V
      // Turn on LED
      PORTB |= (1 << LED_PIN);
    } else {
      // Turn off LED
      PORTB &= ~(1 << LED_PIN);
    }
  }
  
  return 0;
}
*/
/*
#include <avr/io.h>

void adc_setup()
{
  DDRB |= (1 << PB1); // Set PB1 as output for LED
  ADCSRA |= (1 << ADEN); // Enable ADC
  ADMUX |= (1 << REFS1) | (1 << MUX0); // Use external voltage reference and select PB2 as ADC input
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to 128
  ADCSRA |= (1 << ADATE); // Enable auto-trigger
  ADCSRB = 0x00; // Set free running mode
  ADCSRA |= (1 << ADSC); // Start ADC conversion

}

int main()
{
  adc_setup();
  while(1)
  {
    uint8_t adc_l = ADCL; // Read lower byte of ADC result
    uint16_t adc_val = (ADCH << 8) | adc_l; // Combine upper and lower byte of ADC result
    if (adc_val < 819) // Check if voltage is less than 3V (using 4V external reference)
    {
      PORTB |= (1 << PB1); // Turn on LED if voltage is less than 3V
    }
    else
    {
      PORTB &= ~(1 << PB1); // Turn off LED if voltage is greater than or equal to 3V
    }
    ADCSRA |= (1 << ADSC); // Start next ADC conversion
    while(ADCSRA & (1 << ADSC)); // Wait for ADC conversion to complete
  }
}
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

bool yes = false;

void adc_setup()
{
  DDRB |= (1 << PB1);         //PB1 als Ausgang konfigurieren um LED zu aktivieren
  ADCSRA |= (1 << ADEN);      //ADC-Modul aktivieren
  ADMUX = 0x01;               //Konfiguration des ADC-Eingangs auf PB2
  ADCSRB = 0x00;              //Freilaufender Modus konfigurieren
  ADCSRA |= (1 << ADSC) | (1 << ADATE) | (1 << ADIE);   //ADC-Wandlung starten, automatische Auslösung aktivieren und Interrupt aktivieren
}

int main()
{
  adc_setup();
  sei(); //Interrupts aktivieren

  while(1)
  {
    //warten, bis Interrupt ausgelöst wird
  }
}

ISR(ADC_vect) //ADC-Interrupt-Service-Routine
{
//  int adc_l = ADCL; //Wert der Eingangsspannung im unteren Register
//  int adc_val = (ADCH << 8) | adc_l;   //ADCH auslesen und die Daten kombinieren
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));
  uint16_t adc_val = ADC;

  float voltage = (float) adc_val / 1023.0 * 5.0;

  /*
  if (yes == false) {
    PORTB |= (1 << PB1);  //LED einschalten
    yes = true;
    _delay_ms(1000);
  }
  else {
    PORTB &= ~(1 << PB1); //LED ausschalten
    yes = false;
    _delay_ms(1000);
  }
  */

  if (voltage < 4) //LED aktivieren, wenn die Eingangsspannung unter 3V fällt (4V Referenzspannung)
  { 
    PORTB |= (1 << PB1);  //LED einschalten
  }
  else //LED ausschalten, wenn die Eingangsspannung über 3V liegt
  {
    //PORTB &= ~(1 << PB1); //LED ausschalten
  }

  ADCSRA |= (1 << ADIF); //ADC-Interrupt-Flag löschen
}
