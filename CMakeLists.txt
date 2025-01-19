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

if(${CONFIG_SPI})
    list(APPEND DRIVER_SRC
        ${WORKSPACE_BASE}/platform/src/spi.c
    )
endif()

if(${CONFIG_W25Q128JV})
    list(APPEND DRIVER_SRC
        ${WORKSPACE_BASE}/platform/src/w25q128jv.c
    )
endif()