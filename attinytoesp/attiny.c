/*#include <avr/io.h>
#include <util/delay.h>

#define SS_PIN PB5

// SPI Control Register
#define SPCR_REG _SFR_IO8(0x2C)
#define SPE_BIT  6
#define MSTR_BIT 4
#define SPR0_BIT 0

// SPI Data Register
#define SPDR_REG _SFR_IO8(0x2E)

// SPI Status Register
#define SPSR_REG _SFR_IO8(0x2D)
#define SPIF_BIT 7

void spi_init_master() {
    // Set SS pin as output
    DDRB |= (1 << SS_PIN);

    // Set SS pin high initially
    PORTB |= (1 << SS_PIN);

    // Enable SPI, set as Master, and set clock rate fck/16
    SPCR_REG = (1 << SPE_BIT) | (1 << MSTR_BIT) | (1 << SPR0_BIT);
}

void spi_send(uint8_t data) {
    // Select slave (SS pin low)
    PORTB &= ~(1 << SS_PIN);

    // Start transmission
    SPDR_REG = data;

    // Wait for transmission complete
    while (!(SPSR_REG & (1 << SPIF_BIT)));

    // Deselect slave (SS pin high)
    PORTB |= (1 << SS_PIN);
}

int main() {
    // Initialize SPI as Master
    spi_init_master();

    while (1) {
        // Send 'H' over SPI
        spi_send('H');

        _delay_ms(1000);
    }

    return 0;
}
*/

#include <avr/io.h>
#include <util/delay.h>

#define SS_PIN PB5

// SPI Control Register
#define SPCR_REG _SFR_IO8(0x2C)
#define SPE_BIT  6
#define MSTR_BIT 4
#define SPR0_BIT 0

// SPI Data Register
#define SPDR_REG _SFR_IO8(0x2E)

// SPI Status Register
#define SPSR_REG _SFR_IO8(0x2D)
#define SPIF_BIT 7

void spi_init_master() {
    // Set SS pin as output
    DDRB |= (1 << SS_PIN);

    // Set SS pin high initially
    PORTB |= (1 << SS_PIN);

    // Enable SPI, set as Master, and set clock rate fck/16
    SPCR_REG = (1 << SPE_BIT) | (1 << MSTR_BIT) | (1 << SPR0_BIT);
}

void spi_send(uint8_t data) {
    // Select slave (SS pin low)
    PORTB &= ~(1 << SS_PIN);

    // Start transmission
    SPDR_REG = data;

    // Wait for transmission complete
    while (!(SPSR_REG & (1 << SPIF_BIT)));

    // Deselect slave (SS pin high)
    PORTB |= (1 << SS_PIN);
}

int main() {
    // Initialize SPI as Master
    spi_init_master();

    while (1) {
        // Send 'H' over SPI
        spi_send('H');

        _delay_ms(1000);
    }

    return 0;
}
