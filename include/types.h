#ifndef TYPES_H
#define TYPES_H

typedef int s32;
typedef unsigned int u32;
typedef short u16;
typedef unsigned short s16;
typedef char u8;
typedef unsigned char s8;

#define low_16(address) (u16)((address) & 0xffff)
#define high_16(address) (u16)(((address) >> 16) & 0xffff)

#endif
