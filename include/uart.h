#ifndef _UART_H
#define _UART_H

#include "stm32f722xx.h"

#ifndef MAX_PRINT_LENGTH
#define MAX_PRINT_LENGTH 64
#endif

typedef struct {
    USART_TypeDef* uart;
    int baud;
    GPIO_TypeDef* gpio;
    int tx_pin;
    int rx_pin;
    int afr_reg;
    int rx_interrupts;
} USART_Handler;

int init_uart(USART_Handler* u);

int send_uart(USART_TypeDef* u, char* msg, int len);

int print(char *msg);

#endif // _UART_H