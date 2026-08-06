#include "../codexion.h"

void    write_status(t_state status, t_coder *coder)
{
    long    elapsed;

    if (coder->compile_counter == coder->coder_data->number_of_compiles_required)
        return ;
    elapsed = get_time(MILLISECOND) - coder->coder_data->start;
    safe_mutex_handle(&coder->coder_data->write_mutex, LOCK);
    if ((status == TAKE_FIRST_DONGLE || status == TAKE_SECOND_DONGLE) &&
        !simulation_end(coder->coder_data))
        printf("%ld"" %d has taken a dongle\n", elapsed, coder->id);
    else if (status == COMPILE && !simulation_end(coder->coder_data))
        printf("%ld"" %d is compiling\n", elapsed, coder->id);
    else if (status == DEBUG && !simulation_end(coder->coder_data))
        printf("%ld"" %d is debugging\n", elapsed, coder->id);
    else if (status == REFACTOR && !simulation_end(coder->coder_data))
        printf("%ld"" %d is refactoring\n", elapsed, coder->id);
    else if (status == BURNOUT)
        printf("%ld"" %d burned out\n", elapsed, coder->id);
    safe_mutex_handle(&coder->coder_data->write_mutex, UNLOCK);
}