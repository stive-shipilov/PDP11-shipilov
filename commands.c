#include <stdio.h>
#include <stdlib.h>
#include "memory_funcs.h"
#include "mods.h"
#include "flags.h"
#include "load_funcs.h"
#include "math.h"

#define SET_ZERO 0
#define SET_NEGATIVE -1
#define SET_POSITIVE 1

#define SET_CARRY 0x00000

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

void do_movb()
{
    b_write(dd.adr, ss.val);
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
    reg[dd.val] = 0x0000;
    
    set_N(SET_POSITIVE);
    set_Z(SET_ZERO);
    set_C(SET_CARRY);
}

void do_sob()
{
    if(reg[abs(r)] > 1)
    {
        pc = pc - 2*nn;
    }

    (reg[abs(r)])-- ;
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

void do_tst()
{
    set_N(dd.val);
    set_Z(dd.val);
    set_C(SET_CARRY);
}

void do_tstb()
{
    set_N(dd.val);
    set_Z(dd.val);
    set_C(SET_CARRY);
}

void do_bpl()
{    
    if (N == 0)
        do_br();
}

void do_jsr()
{
    w_write(sp, reg[r]);
    reg[r] = pc;
    pc = dd.adr;
    sp -= 2; 

}

void do_rts()
{
    pc = reg[r];
    sp += 2;
    
    reg[r] = w_read(sp);
    w_write(sp, 0);    
}