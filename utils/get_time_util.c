#include "../codexion.h"
#include <sys/time.h>

long    get_time(t_timecode timecode)
{
    struct timeval  tv;
    if (gettimeofday(&tv, NULL))
        error_exit("timeofday failed");
    if (timecode == SECOND)
        return (tv.tv_sec + (tv.tv_usec / 1000000));
    else if (timecode == MILLISECOND)
        return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    else if (timecode == MICROSECOND)
        return ((tv.tv_sec * 1000000) + tv.tv_usec);
    else
        error_exit("Wrong get_time input");
    return (0);
}

void    better_usleep(long usec, t_data *data)
{
    long    start;
    long    elapsed;
    long    rem;

    start = get_time(MICROSECOND);
    while (get_time(MICROSECOND) - start < usec)
    {
        if (simulation_end(data))
            break;
        elapsed = get_time(MICROSECOND) - start;
        rem = usec - elapsed;
        if (rem > 1e3)
            usleep(usec / 2);
        else
            while (get_time(MICROSECOND) - start < usec)
                ;
    }
}