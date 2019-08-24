int make_directory(char **);

int make_directory(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr ,"The syntax of the command is incorrect\n");
    }
    else if (mkdir(args[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
        perror("shell");
    }
    return 1;
}