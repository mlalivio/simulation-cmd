int rname(char **);

// renaming the file
int rname(char **args)
{
    if (rename(args[1], args[2]) == -1)
    {
        perror("shell");
    }
    return 1;
}