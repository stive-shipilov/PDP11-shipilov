#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "commands.h"
#include "memory_funcs.h"
#include "tests.h"
#include "run.h"
#include "load_funcs.h"




int main(int argc, char * argv[])
{
    if(argc - 1 == 0)
    {
        usage(argv[0]);
        exit(1);
    }

    load_file(argv[1]);    
    run();
    

    return 0;
}