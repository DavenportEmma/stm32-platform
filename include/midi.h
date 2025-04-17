#ifndef _MIDI_H
#define _MIDI_H

#include "stm32f722xx.h"

#define STEP_END 0x00
#define SEQ_END 0xFF

typedef enum {
    NOTE_OFF    = 0x80,
    NOTE_ON     = 0x90,
    CONTROLLER = 0xB0,
    USART_START_BYTE = 0xF4,
    USART_END_BYTE = 0xF5
} MIDIStatus_t;

typedef enum {
    CHANNEL_1   = 0x00,
    CHANNEL_2   = 0x01,
    CHANNEL_3   = 0x02,
    CHANNEL_4   = 0x03,
    CHANNEL_5   = 0x04,
    CHANNEL_6   = 0x05,
    CHANNEL_7   = 0x06,
    CHANNEL_8   = 0x07,
    CHANNEL_9   = 0x08,
    CHANNEL_10  = 0x09,
    CHANNEL_11  = 0x0A,
    CHANNEL_12  = 0x0B,
    CHANNEL_13  = 0x0C,
    CHANNEL_14  = 0x0D,
    CHANNEL_15  = 0x0E,
    CHANNEL_16  = 0x0F
} MIDIChannel_t;

typedef enum {
    C8      = 0x6C,
    B7      = 0x6B,
    ASHARP7 = 0x6A,
    A7      = 0x69,
    GSHARP7 = 0x68,
    G7      = 0x67,
    FSHARP7 = 0x66,
    F7      = 0x65,
    E7      = 0x64,
    DSHARP7 = 0x63,
    D7      = 0x62,
    CSHARP7 = 0x61,
    C7      = 0x60,
    B6      = 0x5F,
    ASHARP6 = 0x5E,
    A6      = 0x5D,
    GSHARP6 = 0x5C,
    G6      = 0x5B,
    FSHARP6 = 0x5A,
    F6      = 0x59,
    E6      = 0x58,
    DSHARP6 = 0x57,
    D6      = 0x56,
    CSHARP6 = 0x55,
    C6      = 0x54,
    B5      = 0x53,
    ASHARP5 = 0x52,
    A5      = 0x51,
    GSHARP5 = 0x50,
    G5      = 0x4F,
    FSHARP5 = 0x4E,
    F5      = 0x4D,
    E5      = 0x4C,
    DSHARP5 = 0x4B,
    D5      = 0x4A,
    CSHARP5 = 0x49,
    C5      = 0x48,
    B4      = 0x47,
    ASHARP4 = 0x46,
    A4      = 0x45,
    GSHARP4 = 0x44,
    G4      = 0x43,
    FSHARP4 = 0x42,
    F4      = 0x41,
    E4      = 0x40,
    DSHARP4 = 0x3F,
    D4      = 0x3E,
    CSHARP4 = 0x3D,
    C4      = 0x3C,
    B3      = 0x3B,
    ASHARP3 = 0x3A,
    A3      = 0x39,
    GSHARP3 = 0x38,
    G3      = 0x37,
    FSHARP3 = 0x36,
    F3      = 0x35,
    E3      = 0x34,
    DSHARP3 = 0x33,
    D3      = 0x32,
    CSHARP3 = 0x31,
    C3      = 0x30,
    B2      = 0x2F,
    ASHARP2 = 0x2E,
    A2      = 0x2D,
    GSHARP2 = 0x2C,
    G2      = 0x2B,
    FSHARP2 = 0x2A,
    F2      = 0x29,
    E2      = 0x28,
    DSHARP2 = 0x27,
    D2      = 0x26,
    CSHARP2 = 0x25,
    C2      = 0x24,
    B1      = 0x23,
    ASHARP1 = 0x22,
    A1      = 0x21,
    GSHARP1 = 0x20,
    G1      = 0x1F,
    FSHARP1 = 0x1E,
    F1      = 0x1D,
    E1      = 0x1C,
    DSHARP1 = 0x1B,
    D1      = 0x1A,
    CSHARP1 = 0x19,
    C1      = 0x18,
    B0      = 0x17,
    ASHARP0 = 0x16,
    A0      = 0x15
} MIDINote_t;

typedef enum {
    ALL_NOTES_OFF  = 0X7B
} MIDIControl_t;

typedef enum {
    NO_ERROR            = 0x00,
    SEND_ERR_TIMEOUT    = 0x01
} MIDIError_t;

typedef struct {
    MIDIStatus_t status;
    MIDIChannel_t channel;
    MIDINote_t note;
    char velocity;
} MIDIPacket_t;

typedef struct {
    MIDIStatus_t status;
    MIDIChannel_t channel;
    MIDIControl_t control;
    char value;
} MIDICC_t;

typedef struct {
    uint8_t counter; // this keeps track of the step NOT THE STEP ADDRESS
    MIDIChannel_t channel;
    uint8_t enabled;
    uint32_t enabled_steps[2];
    uint32_t muted_steps[2];
} MIDISequence_t;

int send_midi_note(
    USART_TypeDef* u,
    MIDIPacket_t* p
);

int send_midi_control(
    USART_TypeDef* u,
    MIDICC_t* p
);

void all_channels_off(USART_TypeDef* u);

#endif  // MIDI_H