#ifndef _W25Q128JV_H
#define _W25Q128JV_H

typedef enum {
    PROGRAM_PAGE    = 0x02,
    READ_DATA       = 0x03,
    READ_STATUS_1   = 0x05,
    WRITE_ENABLE    = 0x06,
    SECTOR_ERASE    = 0x20,
    BLOCK_ERASE_64KB = 0xD8,
    CHIP_ERASE      = 0x60,
} W25Q128JV_CMD;

/*
the flash chip is broken into 64k pages, 256 bytes wide
---------------------------------
|   0xFFFF00        0xFFFFFF    |
|   0xFFFE00        0xFFFEFF    |
| ----------------------------- |

| ----------------------------- |
|   0x000000        0x000000    |   
|   0x000000        0x000000    |   
---------------------------------
    <-- page byte address -->

each step is 1 page, this gives us 64k steps

common midi messages
--------------------------------------------------------------------------------
Status    Byte 1    Byte 2    Message           Legend
--------------------------------------------------------------------------------
1000nnnn  0kkkkkkk  0vvvvvvv  Note Off          n=channel k=key v=velocity
1001nnnn  0kkkkkkk  0vvvvvvv  Note On           n=channel k=key v=velocity
1010nnnn  0kkkkkkk  0ppppppp  AfterTouch        n=channel k=key p=pressure
1011nnnn  0ccccccc  0vvvvvvv  Controller Value  n=channel c=controller v=value
1100nnnn  0ppppppp  [none]    Program Change    n=channel p=preset
1101nnnn  0ppppppp  [none]    Channel Pressure  n=channel p=pressure
1110nnnn  0fffffff  0ccccccc  Pitch Bend        n=channel c=coarse f=fine (14b)
--------------------------------------------------------------------------------

the information in byte 2 will be global for all notes played in a step as it
would be too hard for a user to edit these for say a 8 note polyphonic step

step global information
    velocity
    time offset
    gate
*/

/* 
every two bytes after these first 3 are status and key bytes for the notes
note off bytes should always come before note on bytes
*/

void writeEnable();
void eraseSector(uint32_t addr);
void eraseBlock(uint32_t addr);
void eraseChip();
void programPage(uint32_t addr, uint8_t* tx, uint8_t* rx, uint8_t len);
void SPIRead(uint32_t addr, uint8_t* tx, uint8_t* rx, uint8_t len);

#endif // _W25Q128JV_H