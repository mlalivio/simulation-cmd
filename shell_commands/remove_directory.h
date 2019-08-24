int remove_directory(char **);

// removing directory
int remove_directory(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "The syntax of the command is incorrect\n");
    }
    else if (rmdir(args[1]) == -1)
    {
        perror("shell");
    }
    return 1;
}