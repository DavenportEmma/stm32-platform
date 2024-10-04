#ifndef _MENU_H
#define _MENU_H

typedef enum {
    SEQUENCE_SELECT = 0,
    FUNCTION_SELECT = 1,
    STEP_SELECT = 2,
    MODIFY_STEP = 3,
    PITCH_MENU = 4,
    VELOCITY_MENU = 5,
    GLIDE_MENU = 6,
    CHANGE_PRESCALER = 7,
    SET_MIDI_CHANNEL = 8;
    SET_ACTIVE_STEPS = 9;
} MenuLUT;

#endif