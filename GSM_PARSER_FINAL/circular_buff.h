/*
 * circular_buff.h
 *
 *  Created on: 18-Feb-2024
 *      Author: Charge2
 */

#ifndef CIRCULAR_BUFF_H_
#define CIRCULAR_BUFF_H_

#define BUFFER_SIZE 50
typedef struct
{
    char data[BUFFER_SIZE];
    volatile unsigned int head;
    volatile unsigned int tail;
}CircularBuffer;
CircularBuffer buffer;
void cbuff_init();
int isBufferEmpty();
int isBufferFull();
char readFromBuffer();
void writeToBuffer();

#endif /* CIRCULAR_BUFF_H_ */
