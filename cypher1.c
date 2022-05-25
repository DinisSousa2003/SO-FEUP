#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define READ 0
#define Write 1
//chars >64 && chars < 123

int main(int argc, char *argv[])
{

    int ptoc[2]; // parent to children
    int ctop[2]; // children to parent

    pid_t pid;

    if (pipe(ptoc) < 0)
    {
        // pipe failed
        exit(EXIT_FAILURE);
    }
    if (pipe(ctop) < 0)
    {
        // pipe failed
        exit(EXIT_FAILURE);
    }

    char * str = NULL;
    size_t len_str = 0;

    if ((pid = fork()) < 0) // fork
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // children process
    {
        close(ptoc[1]);
        close(ctop[0]);

        while (/* condition */)
        {
            read(ptoc[0], str, );
        }
        
    }

}
