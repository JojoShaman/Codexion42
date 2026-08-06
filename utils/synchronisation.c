#include "../codexion.h"

void    spinlock(t_data *data)
{
    while(!get_bool(&data->data_mutex, &data->all_threads_ready))
        ;
}