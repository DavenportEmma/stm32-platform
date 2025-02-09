#ifndef _K_BUF_H
#define _K_BUF_H

typedef struct {
    uint8_t* buffer;
    int8_t head;    // points to the head element
    int8_t max;     // max number of elements
    int8_t full;
    int8_t ready;
} k_buf_t;

typedef k_buf_t* kbuf_handle_t;

kbuf_handle_t kbuf_init(uint8_t* buffer, uint8_t size);

void kbuf_free(kbuf_handle_t k);

void kbuf_reset(kbuf_handle_t k);

int8_t kbuf_full(kbuf_handle_t k);

int8_t kbuf_empty(kbuf_handle_t k);

int8_t kbuf_size(kbuf_handle_t k);

int8_t kbuf_ready(kbuf_handle_t k);

void kbuf_push(kbuf_handle_t k, uint8_t d);

void kbuf_pop(kbuf_handle_t k, uint8_t* d);

#endif // _K_BUF_H