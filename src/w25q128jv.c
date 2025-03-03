#include "stm32f722xx.h"
#include "spi.h"
#include "uart.h"
#include "w25q128jv.h"

static void compileHeader(uint8_t command, uint32_t addr, uint8_t* header) {
    uint8_t addrB0 = addr & 0xFF;
    uint8_t addrB1 = (addr >> 8) & 0xFF;
    uint8_t addrB2 = (addr >> 16) & 0xFF;

    header[0] = command;
    header[1] = addrB2;
    header[2] = addrB1;
    header[3] = addrB0;
}

static uint8_t busy(void) {
    uint8_t data[] = {READ_STATUS_1, 0x00};
    CS_low(GPIOA, 4);

    SPI_tx_rx(SPI1, data, data, 2);

    CS_high(GPIOA, 4);

    return (data[1] & 0x01);
}

static void sendHeader(uint32_t addr, W25Q128JV_CMD c) {
    uint8_t header[4];
    int8_t rx[4];
    compileHeader(c, addr, header);

    SPI_tx_rx(SPI1, header, rx, 4);
}

void eraseSector(uint32_t addr) {
    while(busy()) {}
    writeEnable();

    CS_low(GPIOA, 4);

    sendHeader(addr, SECTOR_ERASE);

    CS_high(GPIOA, 4);

}

void eraseBlock(uint32_t addr) {
    while(busy()) {}
    writeEnable();

    CS_low(GPIOA, 4);

    sendHeader(addr, BLOCK_ERASE_64KB);

    CS_high(GPIOA, 4);

}

void programPage(uint32_t addr, uint8_t data[], uint8_t len) {
    writeEnable(); 

    CS_low(GPIOA, 4);
    
    sendHeader(addr, PROGRAM_PAGE);

    SPI_tx_rx(SPI1, data, len);

    CS_high(GPIOA, 4);
}

void SPIRead(uint32_t addr, uint8_t data[], uint8_t len) {
    CS_low(GPIOA, 4);

    sendHeader(addr, READ_DATA);

    SPI_tx_rx(SPI1, data, len);

    CS_high(GPIOA, 4);
}

void writeEnable() {
    CS_low(GPIOA, 4);
    uint8_t tx[] = {WRITE_ENABLE};
    SPI_tx_rx(SPI1, tx, 1);
    CS_high(GPIOA, 4);
}