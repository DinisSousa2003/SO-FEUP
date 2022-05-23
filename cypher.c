#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
#define LINESIZE 256

int main(int argc, char *argv[]){

    int nbytes, fd1[2], fd2[2];
    pid_t pid;
    char line[LINESIZE];

    char * content = NULL;
    size_t line_size = 0;
    
    
    if (pipe(fd1) < 0 || pipe(fd2) < 0){
    perror("pipe error");
    exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0){
    perror("fork error");
    exit(EXIT_FAILURE);
    }

    else if (pid > 0){
        while(getline(&content,&line_size, stdin) > 0){
            /* parent */
            printf("%s", content);

            /*write to pipe*/
            close(fd1[READ_END]);
            snprintf(line, LINESIZE, "%s", content);

            if ((nbytes = write(fd1[WRITE_END], line, strlen(line))) < 0){
                fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
            }

            close(fd1[WRITE_END]);

            /*read from pipe*/
        }
    }

    else{
        /* child */

        /*read file*/

        /*read from parent*/
        close(fd1[WRITE_END]);
        if ((nbytes = read(fd1[READ_END], line, LINESIZE)) < 0){
            fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
        }
        close(fd1[READ_END]);
        
        /*cypher the words*/

        /* write message back to parent */
        //write(STDOUT_FILENO, line, nbytes);
    }
}
