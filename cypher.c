#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define test_size sizeof(char)

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

    char *str = NULL;
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
        
        read(ptoc[0], str, test_size);
        close(ptoc[0]);

        //code goes here

        write(ctop[1], str, test_size);
        close(ctop[1]);
        exit(EXIT_SUCCESS);

    }
    else if (pid > 0) // parent process
    {
        close(ptoc[0]);
        close(ctop[1]);

        fseek(stdin, 0, SEEK_END);
        len_str = ftell(stdin);
        fseek(stdin, 0, SEEK_SET);
        str = malloc(sizeof(char) * len_str);
        fread(str, 1, len_str, stdin);

        write(ptoc[1], str, test_size);
        close(ptoc[1]);

        /*if (waitpid(-1, NULL, 0) < 0)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }*/
        str = NULL;
        read(ctop[0], str, test_size);
        close(ctop[0]);

        fprintf(stdout, "%s", str);
    }

    return 0;
}