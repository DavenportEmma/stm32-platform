#ifndef _C_BUF_H
#define _C_BUF_H

typedef struct {
    uint8_t* buffer;
    uint8_t head;
    uint8_t tail;
    uint8_t max;
    uint8_t full;
} circular_buf_t;

typedef circular_buf_t* cbuf_handle_t;

cbuf_handle_t circular_buf_init(uint8_t* b, uint8_t size);

void circular_buf_free(cbuf_handle_t b);

void circular_buf_reset(cbuf_handle_t b);

void circular_buf_put(cbuf_handle_t b, uint8_t data);

uint8_t circular_buf_get(cbuf_handle_t b, uint8_t* data);

int8_t circular_buf_empty(cbuf_handle_t b);

int8_t circular_buf_full(cbuf_handle_t b);

uint8_t circular_buf_size(cbuf_handle_t b);

int8_t circular_buf_index_of(cbuf_handle_t b, uint8_t value);

#endif // _C_BUF_H