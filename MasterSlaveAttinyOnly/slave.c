#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/i2c.h>

#define SLAVE_ADDRESS 0x10

volatile uint8_t received_data;

void i2c_setup(uint8_t address)
{
    TWAR = (address << 1); // Set slave address
    TWCR = (1 << TWEN) | (1 << TWEA); // Enable I²C and enable ACK
}

void i2c_receive()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    received_data = TWDR;
}

void i2c_send(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void initialize_LED()
{
    // Configure the LED pin as an output
    DDRB |= (1 << PB3);
}

void turn_on_LED()
{
    // Turn on the LED
    PORTB |= (1 << PB3);
}

void turn_off_LED()
{
    // Turn off the LED
    PORTB &= ~(1 << PB3);
}

int main()
{
    i2c_setup(SLAVE_ADDRESS);
    initialize_LED();
    sei(); // Enable global interrupts
    
    while (1) {
        // Wait for I²C address match and data received
        while (!(TWCR & (1 << TWINT)));
        if ((TWSR & 0xF8) == TW_SR_SLA_ACK) { // Address match
            i2c_receive(); // Receive data
            if (received_data == 0x01) {
                // Turn on the LED
                turn_on_LED();
            } else {
                // Turn off the LED (or implement other commands)
                turn_off_LED();
            }
        }

        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Enable ACK
    }
}
