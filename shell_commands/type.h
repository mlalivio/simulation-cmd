int type(char **);

// read contents of file
int type(char **args)
{
    int fd;
    if ((fd = open(args[1], O_RDONLY)) == -1)
    {
        perror("shell");
        return 1;
    }
    int len = lseek(fd, 0, SEEK_END);
    void *data = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
    fprintf(stdout, "%s\n", data);
    return 1;
}