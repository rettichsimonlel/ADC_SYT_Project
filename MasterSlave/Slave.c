#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define I2C_SLAVE_ADDRESS 0x12

ISR(TWI_vect)
{
    uint8_t status = TWSR & 0xF8;

    switch (status)
    {
        // SLA+W received, ACK returned
        case TW_SR_SLA_ACK:
            break;

        // data received, ACK returned
        case TW_SR_DATA_ACK:
            uint8_t data = TWDR;
            // do something with the received data
            break;

        // stop or repeated start condition received while addressed as slave
        case TW_SR_STOP:
        case TW_SR_SRF:
            break;

        // default: do nothing
        default:
            break;
    }

    // clear the interrupt flag
    TWCR |= (1 << TWINT);
}

int main(void)
{
    // set I2C slave address
    TWAR = (I2C_SLAVE_ADDRESS << 1);

    // enable I2C slave mode
    TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWEA);

    // enable interrupts
    sei();

    while (1)
    {
        // do nothing
    }

    return 0;
}
