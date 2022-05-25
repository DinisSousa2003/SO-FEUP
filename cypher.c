#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define MSGSIZE 256
#define READ_END 0
#define WRITE_END 1
//chars >64 && chars < 123


int main(int argc, char *argv[])
{

    int ptoc[2]; // parent to children
    int ctop[2]; // children to parent

    pid_t pid;
    char buffer[MSGSIZE];

    if (pipe(ptoc) < 0 || pipe(ctop) < 0)
    {
        // pipe failed
        exit(EXIT_FAILURE);
    }

    memset(buffer, '\0', MSGSIZE);

    if ((pid = fork()) < 0) // fork
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // children process
    {

        char file_name[] = "cypher.txt";

        char end[2];
        memset(end, '\0', 2);
        end[1] = '1';

        close(ptoc[WRITE_END]);
        close(ctop[READ_END]);

        FILE * cypher_file = open(file_name, "r");

        while (fscanf(cypher_file, "%s %s\n", ) > 0)
        {
            /* code */
        }
        

        
  
        //int counter = 1000;
        while (1)
        {
            int r2 = read(ptoc[READ_END], buffer, MSGSIZE);
            //printf("r2: %d\n", r2);

            if(buffer[1] == end[1] && buffer[0] == end[0]) break;

            /*code goes here*/

        
            /*code ends here*/

            int w2 = write(ctop[WRITE_END], buffer, MSGSIZE);
            //printf("w2: %d\n", w2);
        }
        
        close(ptoc[READ_END]);
        close(ctop[WRITE_END]);
        exit(EXIT_SUCCESS);
        
    }
    else if (pid > 0) // parent process
    {
        char x;

        close(ptoc[0]);
        close(ctop[1]);

        int it_counter = 0;


        x = getc(stdin);
        int i = 0;

        while (x != EOF)
        {
            i = 0;
            buffer[i++] = x;

            if(x < 65 || x > 122)
            {
                while(((x = getc(stdin)) != EOF) && ((x < 65) || (x > 122))){
                    buffer[i++] = x;
                }
            }
            else
            {
                while(((x = getc(stdin)) != EOF) && !(x < 65) && !(x > 122)){
                    buffer[i++] = x; 
                }

            }
            buffer[i] = '\0';

            int w1 = write(ptoc[1], buffer, MSGSIZE);
            //printf("w1: %d\n", w1);

            it_counter++;
        }
        buffer[0] = '\0';
        buffer[1] = '1';
        int w1 = write(ptoc[1], buffer, MSGSIZE);

        while(it_counter--){
            //char buffer[MSGSIZE];
            //memset(buffer, '\0', MSGSIZE);
            int r1 = read(ctop[0],buffer , MSGSIZE);
            //printf("r1: %d\n", r1);
            fprintf(stdout, "%s", &buffer[0]);
            

        }
        close(ptoc[1]);
        close(ctop[0]);
        
    }

    return 0;
}