#include "FreeRTOS.h"
#include "k_buf.h"

static void advance_head_pointer(kbuf_handle_t k) {
    k->head++;
    if(k->head >= k->max) {
        k->head = k->max-1;
        k->full = 1;
    }
}

static void retreat_head_pointer(kbuf_handle_t k) {
    if(--k->head < -1) {
        k->head = -1;
    }

    k->full = 0;
}

kbuf_handle_t kbuf_init(uint8_t* buffer, uint8_t size) {
    kbuf_handle_t kbuf = pvPortMalloc(sizeof(k_buf_t));

    kbuf->buffer = buffer;
    kbuf->max = size;
    kbuf_reset(kbuf);

    return kbuf;
}

void kbuf_free(kbuf_handle_t k) {
    vPortFree(k);
}

void kbuf_reset(kbuf_handle_t k) {
    k->head = -1;
    k->full = 0;
    k->ready = 0;
}

int8_t kbuf_full(kbuf_handle_t k) {
    return k->full;
}

int8_t kbuf_empty(kbuf_handle_t k) {
    if(k->head >= 0) {
        return 0;
    } else {
        return 1;
    }
}

int8_t kbuf_ready(kbuf_handle_t k) {
    return k->ready;
}

int8_t kbuf_size(kbuf_handle_t k) {
    return k->head+1;   // return number of elements in array
}

void kbuf_push(kbuf_handle_t k, uint8_t data) {
    advance_head_pointer(k);
    k->buffer[k->head] = data;

}

void kbuf_pop(kbuf_handle_t k, uint8_t* data) {
    if(!kbuf_empty(k)) {
        *data = k->buffer[k->head];
        retreat_head_pointer(k);
    }
}