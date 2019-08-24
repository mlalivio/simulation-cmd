int cd(char **);
int display_current_directory(char **);
int change_current_directory(char **);

int display_current_directory(char **args)
{
    char path[PATH_MAX];
    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("shell");
    }
    printf("%s\n", path);
    return 1;
}

int change_current_directory(char **args)
{
    int pathCount = 1;
    char path[PATH_MAX];
    while (pathCount < ARGS_COUNT)
    {
        if (pathCount != 1)
        {
            char *space = " ";
            strcat(path, space);
        }
        strcat(path, args[pathCount]);
        pathCount++;
    }
    if (chdir(path) != 0)
    {
        perror(path);
    }
    memset(path, 0, sizeof path);
    return 1;
}

int cd(char **args)
{
    if (strcmp(args[0], "cd") == 0 && args[1] == NULL)
    {
        return display_current_directory(args);
    }
    return change_current_directory(args);
}