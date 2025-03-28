#include "stm32f722xx.h"
#include "uart.h"
#include "config.h"

int init_uart(USART_Handler* u) {
    #ifndef SYS_CLK
        #define SYS_CLK 16000000
    #endif

    USART_TypeDef* uart = u->uart;
    GPIO_TypeDef* gpio = u->gpio;

    switch((unsigned long)uart) {
        case (unsigned long)USART1:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
            RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
            RCC->DCKCFGR2 |= (1 << ((1 - 1) * 2));
            break;
        case (unsigned long)USART3:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
            RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
            RCC->DCKCFGR2 |= (1 << ((3 - 1) * 2));
            break;
        default:
            return 1;
    }

    // set alternate mode 7 for tx and rx pins
    gpio->AFR[u->afr_reg] |= (7 << ((u->tx_pin-(8*u->afr_reg))*4)) | (7 << ((u->rx_pin-(8*u->afr_reg))*4));

    gpio->MODER &= ~(0x3 << (u->tx_pin * 2) | 0x3 << (u->rx_pin * 2));  // Clear mode bits for gpio
    gpio->MODER |= (2 << (u->tx_pin * 2)) | (2 << (u->rx_pin * 2));     // set alternate mode for pin
    RCC->CR |= RCC_CR_HSION;    // set high speed mode for usart

    uart->CR1 &= ~(0xFFFFFFFF);   // clear cr1
    uart->BRR |= SYS_CLK / u->baud;  // Assuming APB2 clock is 16 MHz

    if(u->rx_interrupts) {
        uart->CR1 |= (1 << 5);
    }
    
    uart->CR1 |= 0xC; // enable tx ad rx
    uart->CR1 |= 0x1; // enable usart

    return 0;
}

int send_uart(USART_TypeDef* u, char* msg, int len) {
    for(int i = 0; i < len; i++) {
        uint32_t timeout_counter = 0;

        while(!(u->ISR & (1 << 7))) {
            timeout_counter++;
            if(timeout_counter >= SEND_TIMEOUT) {
                return 1;
            }
        }
        u->TDR = msg[i];
    }

    return 0;
}

int print(char *msg) {
    for(int i = 0; i < MAX_PRINT_LENGTH; i++) {
        if(msg[i] == '\0') {
            return 0;
        }

        uint32_t timeout_counter = 0;

        while(!(PRINT_UART->ISR & (1 << 7))) {
            timeout_counter++;
            if(timeout_counter >= SEND_TIMEOUT) {
                return 1;
            }
        }
        PRINT_UART->TDR = msg[i];
    }

    return 0;
}

int getchar() {
    while(!(STLINK_UART->ISR & USART_ISR_RXNE)) {}
    STLINK_UART->RQR |= USART_RQR_RXFRQ;  // Example: Request a flush of the RX buffer (clears RXNE flag)
    return STLINK_UART->RDR - '0';
}