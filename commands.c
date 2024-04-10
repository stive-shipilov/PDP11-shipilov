#include <stdio.h>
#include <stdlib.h>
#include "memory_funcs.h"
#include "mods.h"
#include "flags.h"
#include "math.h"



void do_halt()
{
    reg_dump();
    printf("THE END!\n");
    exit(0);
}

void do_move()
{
    w_write(dd.adr, ss.val);
    set_N(ss.val);
    set_Z(ss.val);
}
void do_add()
{
    w_write(dd.adr, ss.val + dd.val);
    set_N(ss.val + dd.val);
    set_Z(ss.val + dd.val);
    set_C(ss.val + dd.val);
}

void do_unknown()
{
}

void do_clr()
{
    reg[dd.val] = 0;
    set_N(1);
    set_Z(0);
    set_C(0x00000);
}

void do_sob()
{
    if(reg[abs(rl)] > 1)
    {
        pc = pc - 2*nn;
    }

    (reg[abs(rl)])-- ;
}

void do_br()
{
    pc = pc + xx*2;
}

void do_beq()
{
    if (Z == 1)
        do_br();
}
