#include <avr/io.h>
#include <util/delay.h>

char tosend[] = {0x01}; // command to turn on LED

void spi_setup()
{
    DDRB = (1 << PB1) | (1 << PB2); // set MISO and LED pin as output
    USICR = (1 << USIWM0);          // enable three-wire mode (SPI)
}

int main()
{
    spi_setup();

    while (1) {
        // send command to turn on LED
        USIDR = tosend[0];
        USISR = (1 << USIOIF); // clear counter overflow flag
        while ((USISR & (1 << USIOIF)) == 0) {
            USICR |= (1 << USICLK) | (1 << USITC); // enable clock for transmission
        }

        // wait for the slave to respond
        _delay_ms(100);

        // send another command after 5 seconds
        _delay_ms(5000);
    }
}
