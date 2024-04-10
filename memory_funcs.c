#include <stdio.h>
#include "common.h"

static byte mem[PDP11_MEMSIZE];
word reg[8];

byte b_read(adress adr)
{
    return mem[adr];
}

void b_write(adress adr, byte val)
{
    mem[adr] = val;
}

word w_read (adress adr)
{
    word w = mem[adr+1] & 0xFF;
    w = w << 8;
    w = w | (mem[adr] & 0xFF);
    return w;
}

void w_write(adress adr, word val)
{
    if (adr < 8) {
        reg[adr] = val;
        return;
    }
    word w = val;
    mem[adr] = w & 0xFF;
    w = w >> 8;
    mem[adr+1] = w & 0xFF;
}

void reg_dump() {
    for(long unsigned int i = 0; i < sizeof(reg)/sizeof(reg[0]); i++)
    {
        printf("r%ld:%o ", i, reg[i]);
    }
    printf("\n");
}