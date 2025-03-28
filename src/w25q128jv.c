#include "stm32f722xx.h"
#include "spi.h"
#include "uart.h"
#include "w25q128jv.h"

void programPage() {
    writeEnable(); 

    CS_low(GPIOA, 4);

    uint8_t tx[] = {
        0x02,   // page program
        0x00,   // 24b address (0x000000)
        0x00,
        0x00,
        0xDE,
        0xAD,
        0xBE,
        0xEF
    };

    uint8_t rx[8];
    SPI_tx_rx(SPI1, tx, rx, 8);
    CS_high(GPIOA, 4);
}

void SPIRead() {
    CS_low(GPIOA, 4);

    uint8_t tx[] = {
        0x03,   // read
        0x00,   // 24b address (0x000000)
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    uint8_t rx[8];
    SPI_tx_rx(SPI1, tx, rx, 8);
    send_uart(USART3, (char*)&rx, 8);
    CS_high(GPIOA, 4);
}

void writeEnable() {
    CS_low(GPIOA, 4);
    uint8_t tx[] = {0x06};
    uint8_t rx[1];
    SPI_tx_rx(SPI1, tx, rx, 1);
    CS_high(GPIOA, 4);
}