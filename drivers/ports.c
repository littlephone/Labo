/* We use this functions to read and write from the 
 * specific ports. You still cannot access to userspace stdio.h
 * or iostream.h
 */
#include "ports.h"

unsigned char port_byte_in (u16 port){
	unsigned char result;
/*Inline assembly syntax */
	asm("in %%dx, %%al" :"=a"(result): "d" (port));
	return result;
}

void port_byte_out(u16 port, u8 data){
	asm volatile ("out %%al, %%dx"::"a"(data), "d"(port));
}

//This is the same as first function, just difference on type
unsigned short port_word_in (u16 port){
	unsigned short result;
	asm("in %%dx, %%ax": "=a"(result): "d"(port));
	return result;
}

void port_word_out(u16 port, u16 data){
	asm volatile("out %%ax, %%dx":: "a" (data), "d"(port));
}
