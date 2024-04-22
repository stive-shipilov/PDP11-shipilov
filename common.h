#pragma once

#define PDP11_MEMSIZE (64*1024)
#define BYTE 1
#define BYTE_OPCODE 0100000

#define pc reg[7]
#define sp reg[6]

typedef char byte;
typedef int word;
typedef word adress;

extern word reg[8];
extern byte byte_flag;

//NZC
extern byte N, Z, C;




