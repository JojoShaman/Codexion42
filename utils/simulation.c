#include "../codexion.h"

static void debug(t_coder *coder)
{
    int     debug_time;

    debug_time = coder->coder_data->time_to_debug;
    write_status(DEBUG, coder);
    better_usleep(debug_time * 1000, coder->coder_data);
}

static void refactor(t_coder *coder)
{
    int     refactor_time;

    refactor_time = coder->coder_data->time_to_refactor;
    write_status(REFACTOR, coder);
    better_usleep(refactor_time * 1000, coder->coder_data);
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
    better_usleep(coder->coder_data->time_to_compile * 1000, coder->coder_data);
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
    increase_long(&coder->coder_data->data_mutex, &coder->coder_data->threads_running_nbr);
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
        safe_thread_handle(&data->monitor, monitor_data, data, CREATE);
        while (++i < data->number_of_coders)
        {
            safe_thread_handle(&data->coders[i].thread, simulation,
                &data->coders[i], CREATE);
        }
        data->start = get_time(MILLISECOND);
        set_bool(&data->data_mutex, &data->all_threads_ready, true);
        i = -1;
        while (++i < data->number_of_coders)
            safe_thread_handle(&data->coders[i].thread, NULL, NULL, JOIN);
    }

}