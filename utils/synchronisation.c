#include "../codexion.h"
#include <stdbool.h>

void    spinlock(t_data *data)
{
    while(!get_bool(&data->data_mutex, &data->all_threads_ready))
        ;
}

bool    all_coders_running(t_mtx *mutex, long *threads, long coder_nbr)
{
    bool    ret;

    ret = false;
    safe_mutex_handle(mutex, LOCK);
    if (*threads == coder_nbr)
        ret = true;
    safe_mutex_handle(mutex, UNLOCK);
    return (ret);
}

void    increase_long(t_mtx *mutex, long *value)
{
    safe_mutex_handle(mutex, LOCK);
    (*value)++;
    safe_mutex_handle(mutex, UNLOCK);
}