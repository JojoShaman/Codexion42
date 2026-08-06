#include "../codexion.h"

static void debug(t_coder *coder)
{
    write_status(DEBUG, coder);
    better_usleep(coder->coder_data->time_to_debug, coder->coder_data);
}

static void refactor(t_coder *coder)
{
    write_status(REFACTOR, coder);
    better_usleep(coder->coder_data->time_to_refactor, coder->coder_data);
}

static void compile(t_coder *coder)
{
    safe_mutex_handle(&coder->first_dongle->dongle, LOCK);
    write_status(TAKE_FIRST_DONGLE, coder);
    safe_mutex_handle(&coder->second_dongle->dongle, LOCK);
    write_status(TAKE_SECOND_DONGLE, coder);

    set_long(&coder->coder_mutex, &coder->last_compile_time,
        get_time(MILLISECOND));
    coder->compile_counter++;
    write_status(COMPILE, coder);
    better_usleep(coder->coder_data->time_to_compile, coder->coder_data);
    if (coder->coder_data->number_of_compiles_required > 0
        && coder->compile_counter == coder->coder_data->number_of_compiles_required)
        set_bool(&coder->coder_mutex, &coder->end_comp, true);
    safe_mutex_handle(&coder->first_dongle->dongle, UNLOCK);
    safe_mutex_handle(&coder->second_dongle->dongle, UNLOCK);

    
}

static void *simulation(void *data)
{
    t_coder     *coder;

    coder = (t_coder *)data;
    spinlock(coder->coder_data);
    while (!simulation_end(coder->coder_data))
    {
        if (coder->compile_counter == coder->coder_data->number_of_compiles_required)
            break;
        compile(coder);
        debug(coder);
        refactor(coder);
    }
    return (NULL);
}

void    simulation_start(t_data *data)
{
    int     i;

    i = -1;
    if (data->number_of_compiles_required == 0)
        return ;
    else if (data->number_of_coders == 1)
        ; //TODO
    else
    {
        data->start = get_time(MILLISECOND);
        while (++i < data->number_of_coders)
        {
            safe_thread_handle(&data->coders[i].thread, simulation,
                &data->coders[i], CREATE);
        }    
        set_bool(&data->data_mutex, &data->all_threads_ready, true);
        i = -1;
        while (++i < data->number_of_coders)
            safe_thread_handle(&data->coders[i].thread, NULL, NULL, JOIN);
    }

}