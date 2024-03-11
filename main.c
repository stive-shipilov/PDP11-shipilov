#include <stdio.h>
#include <assert.h>

#define PDP11_MEMSIZE (64*1024)

typedef char byte;
typedef int word;
typedef word adress;

byte mem[PDP11_MEMSIZE];

byte b_read(adress adr);
void b_write(adress adr, byte val);
word w_read(adress adr);
void w_write(adress adr, word val);

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
    word w = val;
    mem[adr] = w & 0xFF;
    w = w >> 8;
    mem[adr+1] = w & 0xFF;
}

int main()
{
    
    return 0;
}