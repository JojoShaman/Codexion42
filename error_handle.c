#include "codexion.h"
#include <pthread.h>
#include <sys/_pthread/_pthread_t.h>

void    error_exit(char *error_message)
{
    fprintf(stderr, "%s", error_message);
    exit(EXIT_FAILURE);
}

static void    error_mutex_handle(int status, t_opcode opcode)
{
    if (status == 0)
        return;
    if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
        error_exit("The value specified by mutex is invalid.");
    else if (status == EINVAL && opcode == INIT)
        error_exit("The value specified by attr is invalid.");
    else if (status == EDEADLK)
        error_exit("A deadlock would occur if the"
            " thread blocked waiting for mutex.");
    else if (status == EPERM)
        error_exit("The current thread does not hold a lock on mutex.");
    else if (status == ENOMEM)
        error_exit("The process cannot allocate enough memory to create"
            " another mutex");
    else if (status == EBUSY)
        error_exit("Mutex is locked");
}

void    safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
    if (opcode == LOCK)
        error_mutex_handle(pthread_mutex_lock(mutex), opcode);
    else if (opcode == UNLOCK)
        error_mutex_handle(pthread_mutex_unlock(mutex), opcode);
    else if (opcode == INIT)
        error_mutex_handle(pthread_mutex_init(mutex, NULL), opcode);
    else if (opcode == DESTROY)
        error_mutex_handle(pthread_mutex_destroy(mutex), opcode);
    else
        error_exit("Wrong opcode for mutex handle");
}

static void    error_thread_handle(int status, t_opcode opcode)
{
    if (status == 0)
        return;
    if (status == EAGAIN)
        error_exit("No resource to create another thread.");
    else if (status == EPERM)
        error_exit("The caller does not have appropriate permission.\n");
    else if (status == EINVAL && opcode == CREATE)
        error_exit("The value specified byt attr is invalid.");
    else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
        error_exit("The value specified by thread is not joinable.\n");
    else if (status == ESRCH)
        error_exit("No thread could be found corresponding to that"
            "specified by the given thread ID, thread.");
    else if (status == EDEADLK)
        error_exit("A deadlock was detected or the value of thread"
            "specifies the calling thread.");
}

void    safe_thread_handle(
    pthread_t *thread, void *(*foo)(void *), void* data, t_opcode opcode)
{
    if (opcode == CREATE)
        error_thread_handle(pthread_create(thread, NULL, foo, data), opcode);
    else if (opcode == JOIN)
        error_thread_handle(pthread_join(*thread, NULL), opcode);
    else if (opcode == DETACH)
        error_thread_handle(pthread_detach(*thread), opcode);
    else
        error_exit("Wrong opcode for thread handle");
}
