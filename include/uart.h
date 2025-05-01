#ifndef _UART_H
#define _UART_H

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

int send_hex(USART_TypeDef* u, uint8_t value);

void uart_enable_rx_intr(USART_TypeDef* u);

void uart_disable_rx_intr(USART_TypeDef* u);

#endif // _UART_H