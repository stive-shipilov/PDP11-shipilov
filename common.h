#pragma once

#define PDP11_MEMSIZE (64*1024)

#define pc reg[7]

typedef char byte;
typedef int word;
typedef word adress;

extern word reg[8];

//NZC
extern byte N, Z, C;



