#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
	printf("\n-------------------------\n");
	printf("Welcome, this is a basic linux shell\n");
	printf("Authored by Nathan Wichman and Justin King\n");
	printf("Enter valid linux commands!\n");
	printf("When your done, just type 'exit'\n");
	printf("--------------------------\n\n\n");

	while(1){
	char* params[10];
	char input[100];
	printf("\n\nEnter Command and its parameters (if any): ");
	fgets(input, 100, stdin);
	char* token = strtok(input, " ");
	int i = 0;

	//parsing input string into parameters
	while(token){
		params[i] = token;
		for(int j = 0; j < strlen(params[i]); j++){
			if(params[i][j] == '\n'){
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
		temp[i] = params[i];
		if(params[i] == NULL){
			break;
		}
	}
	
	if(strcmp(temp[0], "exit")==0){
		printf("\nExiting Shell\n\n");
		printf("------------------------\n\n");
		return 0;
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
		if(execvp(temp[0], temp) != 0){
			printf("\nInvalid Linux Command\n");
		}
	}
	//execvp(temp[0], temp);
	}
	return 0;
}
