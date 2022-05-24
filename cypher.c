#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define MSGSIZE 2000
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

    //char *str = NULL;
    char str[MSGSIZE];
    size_t len_str = 0;

	for (int i = 0; i < sizeof(str); i++)
	{
		str[i] = '\0';
	}

    if ((pid = fork()) < 0) // fork
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // children process
    {
        close(ptoc[1]);
        close(ctop[0]);
        
        int r2 = read(ptoc[0], str, MSGSIZE);
        close(ptoc[0]);
        printf("r2: %d\n", r2);

        
        /*code goes here*/

        int w2 = write(ctop[1], str, MSGSIZE);
        close(ctop[1]);

        printf("w2: %d\n", w2);
        exit(EXIT_SUCCESS);

    }
    else if (pid > 0) // parent process
    {
        close(ptoc[0]);
        close(ctop[1]);

        fseek(stdin, 0, SEEK_END);
        len_str = ftell(stdin);
        fseek(stdin, 0, SEEK_SET);
        /*str = malloc(sizeof(char) * len_str);
        fread(str, 1, len_str, stdin);
        */
        char c;
        int x = 0;
        while ((c = getc(stdin)) != '\0')
        {
            if (x > len_str) break;

            str[x] = c;
            x++;
        }
        

        int w1 = write(ptoc[1], str, MSGSIZE);
        close(ptoc[1]);
        printf("w1: %d\n", w1);

        

        int r1 = read(ctop[0], str, MSGSIZE);
        close(ctop[0]);

        printf("r1: %d\n", r1);
        fprintf(stdout, "%s", str);
    }

    return 0;
}