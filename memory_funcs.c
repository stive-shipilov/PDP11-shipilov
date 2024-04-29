#include <stdio.h>
#include "common.h"

static byte mem[PDP11_MEMSIZE];
word reg[8];

byte byte_flag = BYTE;

byte b_read(adress adr)
{
    return mem[adr];
}

void b_write(adress adr, byte val)
{
    mem[adr] = val & 0xFF;
    
}

word w_read (adress adr)
{
    word w = mem[adr+1] & 0xFF;
    w = w << 8;
    w = w | (mem[adr] & 0xFF);
    return w;
    
}

void reg_write(adress adr, word val)
{
    if(byte_flag == BYTE)
    {
        if(((val >> 7) & 0x0001) == 1 )
        {
            val = val | 0xFF00;
        }
        else
        {
            val = val & 0x000FF;
        }
    }
    
    reg[adr] = val & 0xFFFF;
    return;    
}

void w_write(adress adr, word val)
{
    if(adr < 8)
    {
        reg_write(adr, val);
        return;
    }  
    word w = val;
    mem[adr] = w & 0x000FF;
    w = w >> 8;
    mem[adr+1] = w & 0x000FF;    
}

void reg_dump() {
    for(long unsigned int i = 0; i < sizeof(reg)/sizeof(reg[0]); i++)
    {
        printf("r%ld:%06o ", i, reg[i]);
    }
    printf("\n");
}