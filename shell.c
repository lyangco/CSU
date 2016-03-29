#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "grammar.h"

void run_echo(char *ch[], int position);
void run_pwd();
void run_cd(char *ch[]);
void run_env();
void run_setenv(char *ch[]);
void run_exit();
char *getcwd(char *buf, size_t size);
int nextToken;
extern char **environ;
int status;

void get_nexttoken() {
	char *str[20];
	char line[256];
	char *comm;
	int pos = 0;

	if (fgets(line, sizeof line, stdin))
	{
		static const char delim[] = " \n";
		char *token = strtok(line, delim);
		
		while (token)
		{
			str[pos] = token;
			comm = str[0]; 
			token = strtok(NULL, delim);
			pos++;
		}
		if (strcmp (comm, "echo") ==  0 || strcmp (comm, "ECHO") == 0)
		{
			run_echo(str, pos);
			status = 1;
		}
		else if (strcmp (comm, "pwd") == 0 || strcmp(comm, "PWD") == 0)
		{
			run_pwd();
			status = 1;
		}
		else if (strcmp (comm, "cd") == 0 || strcmp(comm, "CD") == 0)
		{
			run_cd(str);
			status = 1;
		}
		else if (strcmp (comm, "env") == 0 || strcmp(comm, "ENV") == 0)
		{
			run_env();
		    status = 1;
		}
		else if (strcmp (comm, "setenv") == 0 || strcmp(comm, "SETENV") == 0)
		{
			run_setenv(str);
			status = 1;
		}
		else if (strcmp (comm, "exit") == 0 || strcmp(comm, "EXIT") == 0)
		{
			run_exit();
			status = 0;
		}
		else
		{
			fprintf(stderr, "Command is invalid\n");
		}
	}
}

void run_echo(char *ch[], int position)
{
	for (int i = 1; i < position; i++)
	{
		printf("%s ", ch[i]);
	}
	printf("\n");
}

void run_pwd()
{
	char cwd[100];
	
	getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}

void run_cd(char *ch[])
{
	char target[100];
	char path[50] = "/";
	char cwd[100];
	
	memset(target, '\0', sizeof(target));
	strcpy(target, ch[1]);
	strcat(path, target);

	if (chdir(path) == 0) {
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
	}
}

void run_env()
{
	int count = 0;
	
	while(environ[count] != NULL)
	{
		printf("%s\n", environ[count]);
		count++;
	}
}

void run_setenv(char *ch[])
{
	int status = 0;
	
	status = setenv(ch[1], ch[2], 1);
}

void run_exit()
{
	exit(0);
}

int main(int argc, char *argv[]) {
	char *com_token[20];
	char *arg[];
	
	do{
	printf("> ");
	get_nexttoken();
	//process(arg);
	} while (status);
	return 0;
}
