#ifndef _MIDI_H
#define _MIDI_H

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
    PORT_A_CHANNEL_1   = 0x00,
    PORT_A_CHANNEL_2   = 0x01,
    PORT_A_CHANNEL_3   = 0x02,
    PORT_A_CHANNEL_4   = 0x03,
    PORT_A_CHANNEL_5   = 0x04,
    PORT_A_CHANNEL_6   = 0x05,
    PORT_A_CHANNEL_7   = 0x06,
    PORT_A_CHANNEL_8   = 0x07,
    PORT_A_CHANNEL_9   = 0x08,
    PORT_A_CHANNEL_10  = 0x09,
    PORT_A_CHANNEL_11  = 0x0A,
    PORT_A_CHANNEL_12  = 0x0B,
    PORT_A_CHANNEL_13  = 0x0C,
    PORT_A_CHANNEL_14  = 0x0D,
    PORT_A_CHANNEL_15  = 0x0E,
    PORT_A_CHANNEL_16  = 0x0F,
    
    PORT_B_CHANNEL_1   = 0x10,
    PORT_B_CHANNEL_2   = 0x11,
    PORT_B_CHANNEL_3   = 0x12,
    PORT_B_CHANNEL_4   = 0x13,
    PORT_B_CHANNEL_5   = 0x14,
    PORT_B_CHANNEL_6   = 0x15,
    PORT_B_CHANNEL_7   = 0x16,
    PORT_B_CHANNEL_8   = 0x17,
    PORT_B_CHANNEL_9   = 0x18,
    PORT_B_CHANNEL_10  = 0x19,
    PORT_B_CHANNEL_11  = 0x1A,
    PORT_B_CHANNEL_12  = 0x1B,
    PORT_B_CHANNEL_13  = 0x1C,
    PORT_B_CHANNEL_14  = 0x1D,
    PORT_B_CHANNEL_15  = 0x1E,
    PORT_B_CHANNEL_16  = 0x1F,
    
    PORT_C_CHANNEL_1   = 0x20,
    PORT_C_CHANNEL_2   = 0x21,
    PORT_C_CHANNEL_3   = 0x22,
    PORT_C_CHANNEL_4   = 0x23,
    PORT_C_CHANNEL_5   = 0x24,
    PORT_C_CHANNEL_6   = 0x25,
    PORT_C_CHANNEL_7   = 0x26,
    PORT_C_CHANNEL_8   = 0x27,
    PORT_C_CHANNEL_9   = 0x28,
    PORT_C_CHANNEL_10  = 0x29,
    PORT_C_CHANNEL_11  = 0x2A,
    PORT_C_CHANNEL_12  = 0x2B,
    PORT_C_CHANNEL_13  = 0x2C,
    PORT_C_CHANNEL_14  = 0x2D,
    PORT_C_CHANNEL_15  = 0x2E,
    PORT_C_CHANNEL_16  = 0x2F,
    
    PORT_D_CHANNEL_1   = 0x30,
    PORT_D_CHANNEL_2   = 0x31,
    PORT_D_CHANNEL_3   = 0x32,
    PORT_D_CHANNEL_4   = 0x33,
    PORT_D_CHANNEL_5   = 0x34,
    PORT_D_CHANNEL_6   = 0x35,
    PORT_D_CHANNEL_7   = 0x36,
    PORT_D_CHANNEL_8   = 0x37,
    PORT_D_CHANNEL_9   = 0x38,
    PORT_D_CHANNEL_10  = 0x39,
    PORT_D_CHANNEL_11  = 0x3A,
    PORT_D_CHANNEL_12  = 0x3B,
    PORT_D_CHANNEL_13  = 0x3C,
    PORT_D_CHANNEL_14  = 0x3D,
    PORT_D_CHANNEL_15  = 0x3E,
    PORT_D_CHANNEL_16  = 0x3F,
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
    // TODO consider consolidating prescale value and counter to reduce memory demands
    int8_t prescale_value;
    int8_t prescale_counter;
    MIDIChannel_t channel;
    uint32_t enabled_steps[2];  // 0 = enabled, 1 = disabled
    uint32_t muted_steps[2];
    /*
        the queue holds information on which sequences are to be started when
        this sequence reaches step 0
    */
    uint32_t queue[2];
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