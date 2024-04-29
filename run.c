#include <stdio.h>
#include "memory_funcs.h"
#include "commands.h"
#include "mods.h"

adress display_status = 0177564;

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_command)(void);
    int arg;
} Command;

#define NOPARAMS 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_NN 4
#define HAS_RL  8
#define HAS_RR  16
#define HAS_XX 32

Command command[14] = {
    {0177777, 0000000, "halt", do_halt, NOPARAMS, },
    {0170000, 0010000, "mov", do_move, HAS_SS | HAS_DD},
    {0170000, 0110000, "movb", do_movb, HAS_SS | HAS_DD},
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0177000, 0077000, "sob", do_sob, HAS_NN | HAS_RL},
    {0177000, 0005000, "clr", do_clr, HAS_DD},
    {0177400, 0000400, "br", do_br, HAS_XX},
    {0177400, 0001400, "beq", do_beq, HAS_XX},
    {0177700, 0005700, "tst", do_tst, HAS_DD},
    {0177700, 0105700, "tstb", do_tstb, HAS_DD},
    {0177400, 0100000, "bpl", do_bpl, HAS_XX},
    {0177000, 0004000, "jsr", do_jsr, HAS_RL | HAS_DD},
    {0177770, 0000200, "rts", do_rts, HAS_RR},

    {0000000, 0000000, "unknown", do_unknown, NOPARAMS},
};


Command find_command(word w)
{
    long unsigned int i;
    for(i = 0; i < sizeof(command) / sizeof(command[0]) ; i++)
    {
        if((w & command[i].mask) == command[i].opcode)
        {
            return command[i];
        }            
    }
    Command z = {0, 0, NULL, NULL, 0};
    return z;
}

void display_init()
{
    w_write(display_status, 0xFFFF);
}


void run()
{
    pc = 01000;
    word w;   

    display_init();  

    while(1) {
        w = w_read(pc);
        printf("%06o %06o: ", pc, w);        
        pc += 2;
        Command cmd = find_command(w);

        byte_flag = !BYTE;
        if((cmd.opcode & BYTE_OPCODE))
            byte_flag = BYTE;

        printf("%s ", cmd.name);

        if(cmd.arg & HAS_RL) 
        {
            r = get_r(w >> 6);
        }
        if(cmd.arg & HAS_RR) 
        {
            r = get_r(w);
        }
        if(cmd.arg & HAS_SS) 
        {
            ss = get_mr(w >> 6);
        }
        if(cmd.arg & HAS_DD) 
        {
            dd = get_mr(w);
        }
        
        if(cmd.arg & HAS_NN) 
        {
            nn = get_nn(w);
        }
        if(cmd.arg & HAS_XX) 
        {
            xx = get_xx(w);
        }
        printf("\n");  
        cmd.do_command(); 
    }
}

