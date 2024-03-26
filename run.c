#include <stdio.h>
#include "memory_funcs.h"
#include "commands.h"
#include "mods.h"

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_command)(void);
    int count_arg;
} Command;

Command command[4] = {
    {0177777, 0000000, "halt", do_halt, 0},
    {0170000, 0010000, "mov", do_move, 2},
    {0170000, 0060000, "add", do_add, 2},


    {0000000, 0000000, "unknown", do_unknown, 0},
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




void run()
{
    pc = 01000;
    word w;    

    while(1) {
        w = w_read(pc);
        printf("%06o %06o: ", pc, w);        
        pc += 2;
        Command cmd = find_command(w);
        printf("%s ", cmd.name);
        if(cmd.count_arg > 0) 
        {
            ss = get_mr(w >> 6);
        }
        if (cmd.count_arg == 2)
        {
            dd = get_mr(w);
        }
        printf("\n");  
        cmd.do_command(); 
    }
}

