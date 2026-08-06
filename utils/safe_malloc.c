#include "../codexion.h"

void    *safe_malloc(size_t size)
{
    void    *alloc;

    alloc = malloc(size);
    if (!alloc)
        error_exit("Allocation error");
    return (alloc);
}