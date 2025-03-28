#include "stm32f722xx.h"
#include "midi.h"
#include "uart.h"

int send_midi_note(
    USART_TypeDef* u,
    MIDIPacket_TypeDef* p
) {
    char buffer[3];
    buffer[0] = p->status | p->channel;
    buffer[1] = p->note;
    buffer[2] = p->velocity;

    return send_uart(u, buffer, 3);
}

int send_midi_control(
    USART_TypeDef* u,
    MIDICC_TypeDef* p
) {
    char buffer[3];
    buffer[0] = p->status | p->channel;
    buffer[1] = p->control;
    buffer[2] = p->value;

    return send_uart(u, buffer, 3);
}

void all_channels_off(USART_TypeDef* u) {
    MIDICC_TypeDef* cc;
    
    for(uint8_t i = 0; i < 16; i++) {
        cc->channel = i;
        cc->status = CONTROLLER;
        cc->control = ALL_NOTES_OFF;
        cc->value = 0;
        send_midi_control(u, cc);
    }
}