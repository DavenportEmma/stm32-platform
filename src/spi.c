#include "spi.h"

int init_spi(SPI_Handler* s) {
    SPI_TypeDef* spi = s->spi;
    GPIO_TypeDef* gpio = s->gpio;

    switch((unsigned long)spi) {
        case (unsigned long)SPI1:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
            RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
            break;
        default:
            return 1;
    }

    // clean mode registers for pins
    gpio->MODER &= ~( (3 << (2 * s->miso)) | (3 << (2 * s->mosi)) | (3 << (2 * s->clk)) | (3 << (2 * s->cs)));
    // set miso, mosi, clk to alternate function, cs to output
    gpio->MODER |= ( (2 << (2 * s->miso)) | (2 << (2 * s->mosi)) | (2 << (2 * s->clk)) | (1 << (2 * s->cs)));
    gpio->AFR[0] |= (5 << (4 * s->miso)) | (5 << (4 * s->mosi)) | (5 << (4 * s->clk));
    gpio->PUPDR &= ~(3 << (s->miso * 2));
    gpio->PUPDR &= ~(3 << (s->mosi * 2));
    gpio->PUPDR |= (1 << (s->miso * 2));
    gpio->PUPDR |= (1 << (s->mosi * 2));

    gpio->ODR |= (1 << s->cs);

    spi->CR1 = 0;
    spi->CR2 = 0;
    spi->CR1 |= SPI_CR1_MSTR;
    spi->CR1 |= SPI_CR1_SSM;
    spi->CR1 |= SPI_CR1_SSI;
    // spi->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2;
    spi->CR2 |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0; // 8-bit data size
    spi->CR2 |= SPI_CR2_FRXTH;
    spi->CR1 |= SPI_CR1_SPE;

    return 0;
}

void SPI_tx_rx(SPI_TypeDef* s, uint8_t* tx, uint8_t* rx, int len) {
    for(int i = 0; i < len; i++) {
        while(!(s->SR & SPI_SR_TXE)) {}
        *(volatile uint8_t*)&s->DR = tx[i];

        while(!(s->SR & SPI_SR_RXNE)) {}
        rx[i] = s->DR;

    }

    while(s->SR & SPI_SR_BSY) {};
}

void CS_low(GPIO_TypeDef* g, int pin) {
    g->ODR &= ~(1 << pin);
}

void CS_high(GPIO_TypeDef* g, int pin) {
    g->ODR |= (1 << pin);
}