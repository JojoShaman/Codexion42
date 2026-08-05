#include "../codexion.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>

void    *safe_malloc(size_t size)
{
    void    *alloc;

    alloc = malloc(size);
    if (!alloc)
        error_exit("Allocation error");
    return (alloc);
}

void    *init_coder()
{
    t_coder thread;
    t_data  *data;
    int index;
    index = 0;
    data->coders = malloc(thread.coder_data->number_of_coders * sizeof(*data->coders));
    if (!data->coders)
        return NULL;
    while (index < thread.coder_data->number_of_coders)
    {
        data->coders[index].id = index + 1;
        data->coders[index].compile_counter = 0;
        // pthread_mutex_lock(&coders[index].lock);
        data->coders[index].last_compile_time = 0;
        // pthread_mutex_unlock(&coders[index].lock);
        index++;
    }
    return NULL;
}