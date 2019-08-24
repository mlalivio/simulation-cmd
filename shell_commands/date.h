#define BUFSIZE_DATE 100
int date(char **);

int date(char **args)
{
    time_t rawtime;
    struct tm *timeinfo;
    struct tm __set_date;
    char _date[BUFSIZE_DATE];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(_date, sizeof(_date), "%A %D", timeinfo);

    fprintf(stdout, "The current date is: %s", _date);

    char *date_input;
    memset(&__set_date, 0, sizeof(__set_date));

    do
    {
        char *set_date = readline("\nEnter date (mm/dd/yy): ");

        if (set_date[0] == '\0')
        {
            break;
        }

        if (strptime(set_date, "%D", &__set_date) == NULL)
        {
            fprintf(stderr, "The system cannot accept the date entered");
        }
        else
        {
            time_t set_time = mktime(&__set_date);
            struct timeval _timeval;
            _timeval.tv_sec = set_time;
            _timeval.tv_usec = 0;

            if (settimeofday(&_timeval, NULL) == -1)
            {
                perror("shell");
            }
            break;
        }
        free(set_date);
    } while (1);

    return 1;
}