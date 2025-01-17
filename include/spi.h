#ifndef _SPI_H
#define _SPI_H

#include "stm32f722xx.h"
#include "autoconf.h"

typedef struct {
    SPI_TypeDef* spi;
    GPIO_TypeDef* gpio;
    int miso;
    int mosi;
    int clk;
    int cs;
} SPI_Handler;

int init_spi(SPI_Handler* s);

void SPI_tx_rx(SPI_TypeDef* s, uint8_t* tx, uint8_t* rx, int len);

void CS_low(GPIO_TypeDef* g, int pin);

void CS_high(GPIO_TypeDef* g, int pin);

#endif // _SPI_H