int remove_files(char**);

// remove files through glob
// in case user types in *.txt, the function would find all files under the .txt extension
int remove_files(char **args)
{
    glob_t file;
    int fileCount = 1;
    int max_args = ARGS_COUNT;

    while(fileCount < max_args)
    {
        if(glob(args[fileCount], 0, NULL, &file))
            perror("Error");
        else {
            for(int i = 0; i < file.gl_pathc; i++)
            {
                if(unlink(file.gl_pathv[i]) == -1)
                {
                    perror("shell");
                }
            }
        }
        fileCount++;
    }
    return 1;
}