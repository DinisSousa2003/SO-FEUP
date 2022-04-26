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
      


	char* phrase = (char*)malloc(MAX_STR_SIZE * sizeof(char));
	int phraseSize = 0, count = 0;
	
	for(int i = 0; i < N; i++) {
		phrase[phraseSize] = txt[i];
		if (txt[i] == '\0') {   //VERIFICAR SE E POSSIVEL
            printf("count : %d \n size : %d", count, phraseSize);
			if (phraseSize != 0) {
                count++;
                if (flagOn) {
                    printf("[%d] %s\n", count, phrase);
                }
            } 
			break;
		}
        else if (txt[i] == '.' || txt[i] == '?' || txt[i] == '!') {
            count++;
            if (flagOn) {
                printf("[%d] %s\n", count, phrase);
            }
            while (txt[i+1] == ' ' || txt[i+1] == '\n' || txt[i+1] == '\t') i++;
            //limpar phrase
            //memset(&phrase, 0, MAX_STR_SIZE);
            phrase = (char*)malloc(MAX_STR_SIZE * sizeof(char));
			phraseSize = 0;
            continue;
		}
        phraseSize++;
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