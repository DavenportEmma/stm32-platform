#include "keyboard.h"
#include "k_buf.h"

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

void readCol(int colIndex, kbuf_handle_t kbuf) {
    static uint16_t prevState[CONFIG_COLUMNS] = {0};

    // read gpioc input register
    int d = GPIOC->IDR;
    uint8_t currentKeyState = 0;
    uint8_t keyVal;
    uint8_t prevKeyState;

    // iterate over each row
    for(int i = 0; i < CONFIG_ROWS; i++) {
        // get key value by masking the associated pin and shifting it right
        currentKeyState = (d >> ROW_LUT[i]) & 1;
        prevKeyState = (prevState[colIndex] >> ROW_LUT[i]) & 1;

        // if the key is pressed
        if(currentKeyState) {
            keyVal = keyMap[colIndex+i*16];
            // if it's a new key press
            if(currentKeyState != prevKeyState) {
                kbuf_push(kbuf, keyVal);
                kbuf->ready = 1;
            // if it's a key hold
            } else {
                kbuf_push(kbuf, keyVal);
            }
        }
    }

    prevState[colIndex] = d;
}

void scan(kbuf_handle_t kbuf) {
    // load a bit into the shift register
    loadBit(1);
    readCol(0, kbuf);
    
    for(int i = 1; i < CONFIG_COLUMNS; i++) {
        loadBit(0);
        readCol(i, kbuf);
    }

    clear();
}