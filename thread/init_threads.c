#include "../codexion.h"

static void     assign_dongle(t_coder *coder, t_dongle *dongle, int position)
{
    int coder_nbr;
    t_dongle    *right_dongle;
    t_dongle    *left_dongle;

    coder_nbr = coder->coder_data->number_of_coders;
    right_dongle = &dongle[position];
    left_dongle = &dongle[(position + 1) % coder_nbr];
    coder->first_dongle = left_dongle;
    coder->second_dongle = right_dongle;
    if (coder->id % 2)
    {
        coder->first_dongle = right_dongle;
        coder->second_dongle = left_dongle;
    }
}
void    init_coder(t_data *data)
{
    int     i;
    t_coder *coder;

    i = -1;
    while (++i < data->number_of_coders)
    {
        coder = &data->coders[i];
        coder->id = i + 1;
        coder->compile_counter = 0;
        coder->coder_data = data;
        coder->end_comp = false;
        safe_mutex_handle(&coder->coder_mutex, INIT);
        assign_dongle(coder, data->dongles, i);
    }
}

void    data_init(t_data *data)
{
    int     i;

    i = -1;
    data->end = false;
    data->all_threads_ready = false;
    data->threads_running_nbr = 0;
    safe_mutex_handle(&data->data_mutex, INIT);
    safe_mutex_handle(&data->write_mutex, INIT);
    data->coders = safe_malloc(
        data->number_of_coders * sizeof(*data->coders));
    data->dongles = safe_malloc(
        data->number_of_coders * sizeof(*data->dongles));
    while (++i < data->number_of_coders)
    {
        safe_mutex_handle(&data->dongles[i].dongle, INIT);
        data->dongles[i].last_released = 0;
        data->dongles[i].dongle_id = i;
    }
}