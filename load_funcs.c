#include <stdio.h>
#include <stdlib.h>
#include "memory_funcs.h"

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