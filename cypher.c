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
        char end[2];
        memset(end, '\0', 2);
        end[1] = '1';

        close(ptoc[WRITE_END]);
        close(ctop[READ_END]);

        FILE * cypher_file;
        char file_name[11] = "cypher.txt";
        char * line = NULL;
        size_t len = 0;

        char **strings1;
        char **strings2;
        int numberOfElements = 0;

        cypher_file = fopen(file_name, "r");
        if(cypher_file == NULL){
            exit (EXIT_FAILURE);
        }

        while (getline(&line, &len, cypher_file) > 0)
        {
            numberOfElements++;
            strings1 = realloc(strings1, numberOfElements * sizeof(char*));
            strings2 = realloc(strings2, numberOfElements * sizeof(char*));

            char *token = strtok(line, " ");
            strings1[numberOfElements - 1] = malloc(strlen(token) * sizeof(char));
            strcpy(strings1[numberOfElements - 1], token);
            
            token = strtok(NULL, " ");
            token[strcspn(token, "\r\n")] = '\0'; 
            strings2[numberOfElements - 1] = malloc(strlen(token) * sizeof(char));
            strcpy(strings2[numberOfElements - 1], token);
        }

        while (1)
        {
            int r2 = read(ptoc[READ_END], buffer, MSGSIZE);
            //printf("r2: %d\n", r2);

            if(buffer[1] == end[1] && buffer[0] == end[0]) break;

            /*code goes here*/
            for(int i = 0; i < numberOfElements; i++){
                if(strcmp(buffer, strings1[i]) == 0){
                    strcpy(buffer, strings2[i]);
                    break;
                }
                if(strcmp(buffer, strings2[i]) == 0){
                    strcpy(buffer, strings1[i]);
                    break;
                }
            }

        
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
            read(ctop[0],buffer , MSGSIZE);
            //printf("r1: %d\n", r1);
            fprintf(stdout, "%s", &buffer[0]);
            

        }
        close(ptoc[1]);
        close(ctop[0]);
        
    }

    return 0;
}