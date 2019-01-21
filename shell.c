#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
	char* params[10];
	char input[100];
	printf("\n\nEnter Command and its parameters (if any): ");
	fgets(input, 100, stdin);
	char* token = strtok(input, " ");
	int i = 0;

	//parsing input string into parameters
	while(token){
		printf("\ntoke: %s", token);
		params[i] = token;
		for(int j = 0; j < strlen(params[i]); j++){
			if(params[i][j] == '\n'){
				printf("\n\nNEWLINE FOUND\n\n");
				params[i][j] = '\0';
				params[i+1] = NULL;
				token = NULL;
				break;
			}
		}
		token = strtok(NULL, " ");
		i++;
	}
	
	char* temp[10];
	for(int i = 0; i < 10; i++){
		printf("\nparams: %s", params[i]);
		temp[i] = params[i];
		if(params[i] == NULL){
			break;
		}
	}

	//Creating child
	int pid = fork();
	if(pid < 0){
		//error has occured
		printf("\nError forking\n");
		return -1;
	}else if(pid > 0){
		//parent
		wait(NULL);
	}else{
		//child
		execvp(temp[0], temp);
	}
	//execvp(temp[0], temp);
	return 0;
}
