#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/i2c.h>

#define SLAVE_ADDRESS 0x10

void i2c_setup()
{
    TWBR = 32; // Set I²C clock frequency to 50kHz (assuming 16MHz CPU clock)
    TWSR = 0;  // Set prescaler bits to 0 for 1:1 prescaler
    TWCR = (1 << TWEN); // Enable I²C
}

void i2c_start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void i2c_stop()
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    _delay_ms(10);
}

void i2c_write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

int main()
{
    i2c_setup();
    
    while (1) {
        i2c_start();
        i2c_write(SLAVE_ADDRESS << 1); // Send slave address with write bit

        // send command to turn on LED
        i2c_write(0x01); // command to turn on LED

        i2c_stop();

        // wait for the slave to respond
        _delay_ms(100);

        // send another command after 5 seconds
        _delay_ms(5000);
    }
}
