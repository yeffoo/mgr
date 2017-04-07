/*
 * buffer.c
 *
 *  Created on: 22 maj 2016
 *      Author: Jeff
 */

#include "buffer.h"

uint8_t buffer1[BUFFER1_SIZE];
uint8_t	buffer1_head = 0, buffer1_tail = 0;

void put_in_buffer1( uint8_t data ) {
	buffer1[buffer1_head] = data;
	if( ++buffer1_head >= BUFFER1_SIZE )
		buffer1_head = 0;
}

uint8_t available_buffer1( void ) {
	return( (buffer1_head - buffer1_tail ) % BUFFER1_SIZE );
}

uint8_t get_from_buffer1( void ) {
	uint8_t data;
	data = buffer1[buffer1_tail];
	if( ++buffer1_tail >= BUFFER1_SIZE )
		buffer1_tail = 0;

	return data;
}

uint8_t buffer2[BUFFER2_SIZE];
uint8_t	buffer2_head = 0, buffer2_tail = 0;

void put_in_buffer2( uint8_t data ) {
	buffer2[buffer2_head] = data;
	if( ++buffer2_head >= BUFFER2_SIZE )
		buffer2_head = 0;
}

uint8_t available_buffer2( void ) {
	return( (buffer2_head - buffer2_tail ) % BUFFER2_SIZE );
}

uint8_t get_from_buffer2( void ) {
	uint8_t data;
	data = buffer2[buffer2_tail];
	if( ++buffer2_tail >= BUFFER2_SIZE )
		buffer2_tail = 0;

	return data;
}
