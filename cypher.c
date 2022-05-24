#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]){

    char * line = NULL;
    size_t len = 0;

    char * ptoc[2]; //parent to children
    char * ctop[2]; //children to parent

    pid_t pid;

    while(getline(&line, &len, stdin) > 0)
    {
        printf("%s", line);
    }

    if (pipe(ptoc < 0))
    {
        //pipe failed
        exit(EXIT_FAILURE);
    }
    if (pipe(ctop) < 0)
    {
        //pipe failed
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) //fork
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) //children process
    {
        close(ptoc[1]);
        close(ctop[0]);
    }
    else if (pid > 0) //parent process
    {
        close(ptoc[0]);
        close(ctop[1]);
    }
    

}