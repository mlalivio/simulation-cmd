static int FIRST_TIME_DISPLAY = 1;
static int ARGS_COUNT = 0;

void shell_loop();
char **split_line(char *);
char* display_current_path();
void restart();
char *concatenate_current_path(char *);
void strcat_beginning(char *dst, const char *src)
{
    size_t dst_len = strlen(dst) + 1, src_len = strlen(src);
    memmove(dst + src_len, dst, dst_len);
    memcpy(dst, src, src_len);
}

#include "shell_commands/command.h"

void shell_loop()
{
	rl_bind_key('\t', rl_insert);

	char *user_input;
	char **tokenized_user_input;
	int status;

	do
	{
		user_input = readline(display_current_path());
		if (strlen(user_input) > 0)
		{
			add_history(user_input);
		}

		tokenized_user_input = split_line(user_input);
		if ((status = execute_command(tokenized_user_input)) == INT_MAX)
		{
			restart();
		}

		free(user_input);
		free(tokenized_user_input);
	} while (status && user_input != NULL);
}

void restart()
{
	FIRST_TIME_DISPLAY = 1;
}

char* display_current_path()
{
	if (FIRST_TIME_DISPLAY)
	{
		const char *CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		FIRST_TIME_DISPLAY = 0;

		fprintf(stdout, "A simple shell created by Michael Loewe Alivio\n");
		fprintf(stdout, "(c) CMSC 125 PROJECT\n");
	}
	static char path[PATH_MAX];
	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("error");
	}

	ARGS_COUNT = 0;

	return concatenate_current_path(path);
}

char *concatenate_current_path(char *current_path)
{
	char *newLine = "\nshell: ";
	char *input_header = "> ";
	strcat_beginning(current_path, newLine);
	strcat(current_path, input_header);
	return current_path;
}

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMETER " \t\r\n\a"

char **split_line(char *line)
{
	int bufsize = TOKEN_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIMETER);

	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += TOKEN_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIMETER);
	}
	ARGS_COUNT = position;
	tokens[position] = NULL;
	return tokens;
}