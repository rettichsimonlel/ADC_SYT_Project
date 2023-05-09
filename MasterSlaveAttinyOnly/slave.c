#include <avr/io.h>
#include <util/delay.h>

char received[200];

void spi_setup()
{
    DDRB = (1 << PB1) | (1 << PB3);  // set MOSI and SCK as output
    USICR = (1 << USIWM0);          // enable three-wire mode (SPI)
}

int main()
{
    spi_setup();

    while (1) {
        // wait for a command
        int i = 0;
        while (1) {
            received[i] = USIBR;
            if (USISR & (1 << USIOIF)) { // check for end of transmission
                USISR |= (1 << USIOIF); // clear counter overflow flag
                break;
            }
            i++;
        }

        // turn on LED if command is to turn on
        if (received[0] == 0x01) {
            PORTB |= (1 << PB3); // turn on LED
            _delay_ms(200);
            PORTB &= ~(1 << PB3); // turn off LED
            _delay_ms(400);
        }
    }
}
