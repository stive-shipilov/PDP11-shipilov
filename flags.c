#include "common.h"

byte N, Z, C;

void set_N(word n_val)
{
    N = 0;   
    if(byte_flag == BYTE)
        N = ((n_val >> 7) & 0x0001);
    else
        N = ((n_val >> 15) & 0x0001);
}

void set_Z(word z_val)
{
    Z = 0;
    if(byte_flag == BYTE)
        Z = ((z_val & 0x00FF) == 0x0000);
    else
        Z = ((z_val & 0xFFFF) == 0x0000);
}

void set_C(word c_val)
{
    C = 0x0001 & (c_val >> 16);
}