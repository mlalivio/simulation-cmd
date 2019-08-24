int cls(char **);

int cls(char **args)
{
    const char *CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
    return 1;
}