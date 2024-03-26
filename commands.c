#include <stdio.h>
#include <stdlib.h>
#include "memory_funcs.h"
#include "mods.h"


void do_halt()
{
    reg_dump();
    printf("THE END!\n");
    exit(0);
}

void do_move()
{
    w_write(dd.adr, ss.val);
}
void do_add()
{
    w_write(dd.adr, ss.val + dd.val);
}

void do_unknown()
{

}