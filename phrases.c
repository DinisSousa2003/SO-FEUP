#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_SIZE 64

int main(int argc, char* argv[]){

    if (argc == 1) {
		printf("usage: phrases [-l] file.\n");
		return 0;
	} 

    if (argc > 3) {
		printf("Wrong usage: phrases [-l] file.\n");
		return 1;
	} 

    int flagOn = 0;

    if (argc == 3){
        if (strcmp(argv[1], "-l") == 0){
            flagOn = 1;
        }
        else{
            printf("Invalid flag: phrases [-l] file.\n");
            return 1;
        }
    }

    //OPENS FILE - FIRST ARGUMENT
    //*fp - file pointer
    //*txt - text pointer
    //N - number of chars
    int fileNumber = flagOn + 1;
    FILE *fp;
    char *txt;
    fp = fopen(argv[fileNumber], "r");
    if(fp == NULL){
        printf("Error opening the file.\n");
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    int N = ftell(fp);
    txt = (char*) malloc(N+1*sizeof(char));
    fseek(fp, 0, SEEK_SET);
    fread(txt, N+1, 1, fp);
    //printf("%s", txt);
    fclose(fp);
      


	
	int phraseSize = 0, count = 0;
    char* phrase = (char*)malloc(sizeof(char) * 1);
    phrase[0] = '\0';
	
	for(int i = 0; i < N; i++) {
        phrase = realloc(phrase, sizeof(char) * phraseSize + 2);
		phrase[phraseSize] = txt[i];
        phrase[phraseSize + 1] = '\0';
        phraseSize++;

        if (txt[i] == '.' || txt[i] == '?' || txt[i] == '!') {
            count++;
            if (flagOn) {
                printf("[%d] %s\n", count, phrase);
            }
            while (txt[i+1] == ' ' || txt[i+1] == '\n' || txt[i+1] == '\t' || txt[i+1] == '\r'){
                i++;
            }
            phrase = (char*)malloc(sizeof(char) * 1);
            phrase[0] = '\0';
			phraseSize = 0;
            continue;
		}
	}
    
    if (phraseSize != 0) {
        count++;
        if (flagOn) {
            printf("[%d] %s\n", count, phrase);
        }
    } 

    if (!flagOn) printf("%d \n",count);
	

    return EXIT_SUCCESS;
}