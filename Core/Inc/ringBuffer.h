//
// Created by benrit on 10/6/23.
//

#ifndef STM32F429_TEST1_RINGBUFFER_H
#define STM32F429_TEST1_RINGBUFFER_H

#include "stdint.h"


#define BUFFER_SIZE 2048

typedef struct {
    uint32_t buffer[BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
} RingBuffer;


void Ring_Buffer_Init(RingBuffer *rb){
    rb->head = 0;
    rb->tail = 0;
}


void Ring_Buffer_Enqueue(RingBuffer *rb, uint32_t data){
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % BUFFER_SIZE;
    if(rb->head == rb->tail){
        rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    }
}


#endif //STM32F429_TEST1_RINGBUFFER_H
