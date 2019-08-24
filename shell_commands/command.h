// an interface for all shell commands
#include "display_directory.h"
#include "change_directory.h"
#include "make_directory.h"
#include "remove_directory.h"
#include "exit.h"
#include "clear.h"
#include "copy.h"
#include "move.h"
#include "date.h"
#include "remove.h"
#include "rename.h"
#include "type.h"
#include "cmd.h"
#include "localtime.h"

int execute(char **);
int shell_launch(char **);
int builtins_length();
int shell_help();

struct Builtin
{
	char *name;
	int (*func)(char **);
	char *help_func;
};

struct Builtin builtins[] = {
	{"cd", &cd, "changes the current directory. If there is no parameter, it displays the current path. cd [PATHNAME]"},
	{"chdir", &cd, "changes the current directory. chdir [PATHNAME]"},
	{"exit", &exit_shell, "exits from the shell"},
	{"dir", &dir, "displays and lists down the subdirectories and files of the current directory"},
	{"cls", &cls, "clears screen"},
	{"copy", &copy, "copies old file to another file or directory. copy [filename] [PATHNAME]"},
	{"move", &move, "moves a file or multiple files on a specified directory. move [filename] [PATHNAME], move [filename] ... [filename] [PATHNAME], move [*.<some extension>] [PATHNAME]"},
	{"mkdir", &make_directory, "creates a new directory. mkdir [directory name], mkdir [PATH]"},
	{"date", &date, "displays and sets date"},
	{"del", &remove_files, "deletes a file or multiple files in current directory. del [filename], del [filename] ... [filename], del [*.<some extension>]"},
	{"rmdir", &remove_directory, "removes an empty directory. rmdir [directory name]"},
	{"type", &type, "displays the contents of a file. type [filename]"},
	{"cmd", &cmd, "calls a new shell"},
	{"time", &localTime, "displays and sets time"},
	{"rename", &rname, "renames a file or directory. rename [old filename] [new filename], rename [old directory] [new directory]"},
	{"help", &shell_help, "displays and lists down a basic functionality on each builtin functions"}
};

int builtins_length()
{
	return *(&builtins + 1) - builtins;
}

/*
	@params - args - tokenized string array
*/
int execute_command(char **args)
{
	if (args[0] == NULL)
	{
		return 1;
	}
	for (int i = 0; i < builtins_length(); i++)
	{
		if(strcmp(args[0], "help") == 0)
		{
			return shell_help();
		}
		else if (strcmp(args[0], builtins[i].name) == 0)
		{
			return builtins[i].func(args);
		}
	}
	return shell_launch(args);
}

/*
	@params args - represents the tokenized user input
*/
int shell_launch(char **args)
{
	pid_t pid, wpid;
	int CHILD_PROCESS = 0;
	int status;

	pid = fork();

	if (pid == CHILD_PROCESS)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("shell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("shell");
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int shell_help()
{
	fprintf(stdout, "A simple shell version. A hybrid implementation of both command prompt in Windows and shell in Linux.\n\n");

	for(int i = 0; i < builtins_length(); i++)
	{
		fprintf(stdout, "[%i] %s - %s\n\n", i+1,builtins[i].name, builtins[i].help_func);
	}
	return 1;
}