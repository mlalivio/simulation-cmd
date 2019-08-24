#define __USE_XOPEN
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <limits.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <readline/readline.h>
#include <readline/history.h>
// "C://cygwin64//lib//gcc//x86_64-pc-cygwin//7.3.0//include",

#include "handler.h"

int main(int argc, char **argv)
{
    
    shell_loop();

    return EXIT_SUCCESS;
}
