int move(char **);
int perform_move(pid_t pid, glob_t file, int status, char *destination);

int move(char **args)
{
    if (args[1] == NULL || ARGS_COUNT < 3)
    {
        fprintf(stderr, "The syntax of the command is incorrect\n");
    }
    else
    {
        glob_t file;
        int max_args = ARGS_COUNT;
        char path[PATH_MAX];
        int filesCounts = 1;
        int destination = ARGS_COUNT - 1;
        int childExitStatus;
        pid_t pid;

        while (filesCounts < destination)
        {
            if (glob(args[filesCounts], 0, NULL, &file))
            {
                perror("shell");
            }
            else
            {
                pid = fork();

                if (pid == 0)
                {
                    pid_t new_pid;
                    int new_status;
                    perform_move(new_pid, file, new_status, args[destination]);
                }
                else if (pid < 0)
                {
                    perror("shell");
                }
                else
                {
                    pid_t ws = waitpid(pid, &childExitStatus, WUNTRACED);
                }
            }
            filesCounts++;
        }
    }
    return 1;
}

int perform_move(pid_t pid, glob_t file, int status, char *destination)
{
    for (int i = 0; i < file.gl_pathc; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            if (execl("/bin/mv", "/bin/mv", file.gl_pathv[i], destination, (char *)0) == -1)
            {
                perror("shell");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else if (pid < 0)
        {
            perror("shell");
            exit(EXIT_FAILURE);
        }
        else
        {
            pid_t new_ws = waitpid(pid, &status, WUNTRACED);
        }
    }
    return 1;
}