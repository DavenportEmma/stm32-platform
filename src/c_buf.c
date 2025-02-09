#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "c_buf.h"

static inline uint8_t advance_headtail_value(uint8_t value, uint8_t max) {
	if(++value == max)
	{
		value = 0;
	}

	return value;
}

static void advance_head_pointer(cbuf_handle_t b) {
	if(circular_buf_full(b))
	{
		b->tail = advance_headtail_value(b->tail, b->max);
	}

	b->head = advance_headtail_value(b->head, b->max);
	b->full = (b->head == b->tail);
}

cbuf_handle_t circular_buf_init(uint8_t* buffer, uint8_t size) {
	cbuf_handle_t cbuf = pvPortMalloc(sizeof(circular_buf_t));

	cbuf->buffer = buffer;
	cbuf->max = size;
	circular_buf_reset(cbuf);

	if(!circular_buf_empty(cbuf)) {
		// buffer reset failed
	}

	return cbuf;
}

void circular_buf_free(cbuf_handle_t b) {
	vPortFree(b);
}

void circular_buf_reset(cbuf_handle_t b) {
	b->head = 0;
	b->tail = 0;
	b->full = 0;
}

void circular_buf_put(cbuf_handle_t b, uint8_t data) {
	b->buffer[b->head] = data;

	advance_head_pointer(b);
}

uint8_t circular_buf_get(cbuf_handle_t b, uint8_t* data) {
	uint8_t r = 0xFF;

	if(!circular_buf_empty(b))
	{
		*data = b->buffer[b->tail];
		b->tail = advance_headtail_value(b->tail, b->max);
		b->full = 0;

		r = 0;
	}

	return r;
}

int8_t circular_buf_empty(cbuf_handle_t b) {
	return (!circular_buf_full(b) && (b->head == b->tail));
}

int8_t circular_buf_full(cbuf_handle_t b) {
	return b->full;
}

uint8_t circular_buf_size(cbuf_handle_t b) {
	uint8_t size = b->max;

	if(!circular_buf_full(b))
	{
		if(b->head >= b->tail)
		{
			size = (b->head - b->tail);
		}
		else
		{
			size = (b->max + b->head - b->tail);
		}
	}

	return size;
}

int8_t circular_buf_index_of(cbuf_handle_t b, uint8_t value) {
	uint8_t size = circular_buf_size(b);
	
	uint8_t pos = b->tail;
	for(int i = 0; i < size; i++) {
		if(b->buffer[pos] == value) {
			return pos;
		}
		pos = advance_headtail_value(pos, b->max);
	}

	return -1;
}
