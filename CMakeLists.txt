cmake_minimum_required(VERSION 3.27.1)

if(${CONFIG_UART})
    list(APPEND DRIVER_SRC
        ${WORKSPACE_BASE}/platform/src/uart.c
    )
endif()

if(${CONFIG_MIDI})
    list(APPEND DRIVER_SRC
        ${WORKSPACE_BASE}/platform/src/midi.c
    )
endif()