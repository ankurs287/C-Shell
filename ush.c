#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define LEN 1000

int main(int argc, char const *argv[])
{
	char* arguments[LEN];
	while(1){
		printf("ush>> ");

		char commandinput[LEN];
		fgets(commandinput, LEN, stdin);

		int inputlen=strlen(commandinput);
		if(inputlen==1){
			continue;
		}
		for (int i = 0; i<inputlen; ++i){
			if(commandinput[i]=='\n'){
				commandinput[i]='\0';
			}
		}

		// fputs("Hello world", stdout);
		if(strcmp(commandinput, "exit")==0){
			fputs("Exiting Shell.\n", stdout);
			break;
		}

		char* tokens=strtok(commandinput," ");
		int lenOfTokens=strlen(tokens);
		for (int i = 0; i < lenOfTokens; ++i){
			arguments[i]=tokens;
			tokens = strtok(NULL," ");
			// tokens*++;
		}
		arguments[lenOfTokens]=NULL;

		if(strcmp(arguments[0], "cd")==0){
			chdir(arguments[1]);
		}

		int pid= fork();
		int waitingpid;
		int status;
		
		if(pid == 0){
			// A Child process
			execvp(arguments[0], arguments);

			exit(EXIT_FAILURE);
		} 
		else{
			// Parent process
			wait(NULL); // 

			fputs("Child Process Done.\n", stdout);
		}
	}
	return 0;
}