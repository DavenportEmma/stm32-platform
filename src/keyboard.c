#include "keyboard.h"

void kb_reset(kb_handle_t kb) {
    kb->hold = 0;
    kb->key = 0;
    kb->ready = 0;
}

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

void readCol(int colIndex, kb_handle_t kb) {
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
                kb->key = keyVal;
                kb->ready = 1;
            // if it's a key hold
            } else {
                kb->hold = keyVal;
            }
        }
    }

    prevState[colIndex] = d;
}

void scan(kb_handle_t kb) {
    // load a bit into the shift register
    loadBit(1);
    readCol(0, kb);
    
    for(int i = 1; i < CONFIG_COLUMNS; i++) {
        loadBit(0);
        readCol(i, kb);
    }

    clear();
}