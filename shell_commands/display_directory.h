#define MAXLEVEL 1

int dir(char **);
int display_info(const char *, const struct stat *, int, struct FTW *);
int args_length(char**);

int args_length(char **args) {
    return *(&args + 1) - args;
}

int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
    if (ftwbuf->level > MAXLEVEL)
    {
        return 0;
    }
    fprintf(stdout, "%-3s ",
            (tflag == FTW_D) ?   "<DIR>"   : (tflag == FTW_DNR) ? "dnr" :
            (tflag == FTW_F) ? "     " : (tflag == FTW_NS) ?  "ns" : 
            (tflag == FTW_SL) ?  "sl" : (tflag == FTW_SLN) ? "sln" : "?");

    if (tflag == FTW_NS)
        fprintf(stdout ,"-------");
    else
        fprintf(stdout, "%7jd", (intmax_t) sb->st_size);

    fprintf(stdout, "   %s\n", fpath + ftwbuf->base);
    return 0;
}

// TODO work more on optional parameters
int dir(char **args) {
    int flags = 0;
    int fd_limit = 20;

    if (nftw((args[1] == NULL) ? "." : args[1], display_info, fd_limit, flags) == -1)
    {
        perror("shell");
    }

    return 1;
}