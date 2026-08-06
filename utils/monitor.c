#include "../codexion.h"
#include <stdbool.h>

bool    coder_burned_out(t_coder *coder)
{
    long    elapsed;
    long    t_to_burnout;

    if (get_long(&coder->coder_mutex, &coder->last_compile_time) <= 0)
        return (false);
    elapsed = get_time(MILLISECOND) - get_long(&coder->coder_mutex, &coder->last_compile_time);
    t_to_burnout = coder->coder_data->time_to_burnout;
    if (elapsed > t_to_burnout)
        return (true);
    return (false);
}

void    *monitor_data(void *simulation_data)
{
    t_data  *data;
    int     i;

    data = (t_data *)simulation_data;
    while (!all_coders_running(&data->data_mutex, &data->threads_running_nbr,
            data->number_of_coders))
        ;
    
    while (!simulation_end(data))
    {
        i = -1;
        while (++i < data->number_of_coders && !simulation_end(data))
        {
            if (coder_burned_out(&data->coders[i]))
            {
                set_bool(&data->data_mutex, &data->end, true);
                write_status(BURNOUT, &data->coders[i]);
            }
        }

    }

    return (NULL);
}