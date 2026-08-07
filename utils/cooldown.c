#include "../codexion.h"

void    dongle_cooldown(t_dongle *dongle, t_data *data)
{
    long    elapsed;

    if (dongle->last_released == 0)
        return ;
    elapsed = get_time(MILLISECOND) - dongle->last_released;
    if (elapsed < (long)data->dongle_cooldown)
        better_usleep((data->dongle_cooldown - elapsed) * 1e3, data);
}