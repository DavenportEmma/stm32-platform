#include "keyboard.h"
#include "autoconf.h"
#include "c_buf.h"

void clear() {
    GPIOD->ODR &= ~CLR;
    GPIOD->ODR |= CLR;
}

void loadBit(int b) {
    GPIOD->ODR |=  ((b << DIN_OFFSET) & DIN);
    GPIOD->ODR |= CLK;
    GPIOD->ODR &= ~(0x1 << DIN_OFFSET);
    GPIOD->ODR &= ~CLK;
}

void readCol(int colIndex, cbuf_handle_t cbuf) {
    // read gpioc input register
    int d = GPIOC->IDR;
    uint8_t keyVal = 0;
    // iterate over each row
    for(int i = 0; i < CONFIG_ROWS; i++) {
        // get key value by masking the associated pin and shifting it right
        keyVal = (d >> ROW_LUT[i]) & 1;

        if(keyVal) {
            circular_buf_put(cbuf, keyMap[colIndex+i*16]);
        }
    }
}

void scan(cbuf_handle_t cbuf) {
    // load a bit into the shift register
    loadBit(1);
    readCol(0, cbuf);
    
    for(int i = 1; i < CONFIG_COLUMNS; i++) {
        loadBit(0);
        readCol(i, cbuf);
    }

    clear();
}