#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define PDP11_MEMSIZE (64*1024)
#define pc reg[7]

typedef char byte;
typedef int word;
typedef word adress;

typedef struct {
    word mask;
    word opcode;
    char * name;
    (void *)do_command(void);
} Command;

Command command[] = {
    {0177777, 0000000, "halt", do_halt},
    {0170000, 0010000, "mov", do_move},
    {0170000, 0060000, "add", do_add},
}

void do_halt()
{
    printf("THE END!!!\n");
    exit(0);
}

void do_halt()
{
    printf("halt");
}

void do_move()
{
    printf("move");
}

byte mem[PDP11_MEMSIZE];
word reg[8];


byte b_read(adress adr);
void b_write(adress adr, byte val);
word w_read(adress adr);
void w_write(adress adr, word val);

void test_mem()
{
    adress a;
    byte b0, b1, bres;
    word w, wres;
    // пишем байт, читаем байт по четному адресу
    fprintf(stderr, "Пишем и читаем байт по четному адресу\n");
    a = 0;
    b0 = 0x77;
    b_write(a, b0);
    bres = b_read(a);
    fprintf(stderr, "a=%06o b0=%x bres=%x\n", a, b0, bres);
    assert(b0 == bres);

    // пишем байт, читаем байт по НЕчетному адресу
    fprintf(stderr, "Пишем и читаем байт по НЕчетному адресу\n");
    a = 1;
    b0 = 0xdf;
    b_write(a, b0);
    bres = b_read(a);
    fprintf(stderr, "a=%06o b0=%x bres=%x\n", a, b0, bres);
    assert(b0 == bres);

    // пишем слово, читаем слово
    fprintf(stderr, "Пишем и читаем слово\n");
    a = 2;        // другой адрес
    w = 0xabcd;
    w_write(a, w);
    wres = w_read(a);
    fprintf(stderr, "a=%06o w=%04x wres=%04x\n", a, w, wres);
    assert(w == wres);

    // Прочитаем записанное слово по байту
    fprintf(stderr, "Прочитаем записанное слово по байту\n");
    byte b1res, b2res;
    a = 4;
    w = 0x7891;
    b1res = 0x91;
    b2res = 0x78;
    w_write(a, w);
    fprintf(stderr, "a=%06o w1=%02x wres1=%02x\n", a, b1res, b_read(a));
    fprintf(stderr, "a=%06o w2=%02x wres2=%02x\n", a+1, b2res, b_read(a+1));
    assert(b1res == b_read(a));
    assert(b2res == b_read(a+1));

    // пишем 2 байта, читаем 1 слово
    fprintf(stderr, "Пишем 2 байта, читаем слово\n");
    a = 4;      
    w = 0xdcba;
    b0 = 0xba;
    b1 = 0xdc;
    b_write(a, b0);
    b_write(a+1, b1);
    wres = w_read(a);
    fprintf(stderr, "a=%06o b1=%02x b0=%02x wres=%x\n", a, b1, b0, wres);
    assert(w == wres);
}

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

void load_data(FILE * stream)
{
    adress a;
    int n;
    byte num;
    while(2 == fscanf(stream, "%x%x", &a, &n))
    {        
        for(int i = 0; i < n; i++)
        {            
            fscanf(stream, "%hhx", &num);
            b_write(a+i, num);              
        }
    }
}

void load_file(const char * filename)
{
    FILE * file = fopen(filename, "r");
    if(file == NULL)
    {
        perror(filename);
        exit(1);
    }
    load_data(file);
    fclose(file);

}

void mem_dump(adress adr, int size)
{
    int size_words = 2*sizeof(byte);

    for(int i = 0; i < size / size_words; i++)
    {
        word number = w_read(adr + i*2);
        printf("%06o: %06o %04x\n" , adr + i*2, number, number);
    }
    
}

void usage(const char * progname)
{
    printf("USAGE: %s file \n file - PDP-11 execution file \n", progname);
}


int main(int argc, char * argv[])
{
    if(argc - 1 == 0)
    {
        usage(argv[0]);
        exit(1);
    }

    load_file(argv[1]);
    
    return 0;
}