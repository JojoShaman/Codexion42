/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.h                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: srosu <srosu@student.42belgium.be>        #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/31 17:07:30 by srosu            #+#    #+#              */
/*   Updated: 2026/07/31 19:23:06 by srosu           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <errno.h>
# include <stdbool.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;33m"
# define RST "\033[0m"

# define USAGE  "Usage: ./codexion " \
        "<number_of_coders> " \
        "<time_to_burnout> " \
        "<time_to_compile> " \
        "<time_to_debug> " \
        "<time_to_refactor> " \
        "<number_of_compiles_required> " \
        "<dongle_cooldown> " \
        "<scheduler>\n"

typedef pthread_mutex_t t_mtx;
typedef struct s_dongle t_dongle;
typedef struct s_coder t_coder;

typedef struct s_data
{
    size_t 	            number_of_coders;
	size_t              time_to_burnout;
	size_t	            time_to_compile;
	size_t	            time_to_debug;
	size_t  	        time_to_refactor;
	size_t	            number_of_compiles_required;
	size_t	            dongle_cooldown;
    size_t              start;
    bool                end;
    bool                all_threads_ready;
    t_mtx               data_mutex;
    t_mtx               write_mutex;
	char                *scheduler;
    t_coder             *coders;
    t_dongle            *dongles;
    pthread_t           monitor;
    long                threads_running_nbr;

}	t_data;

struct s_coder
{
    int                 id;
    bool                end_comp;
    t_data              *coder_data;
    t_dongle            *first_dongle;          
    t_dongle            *second_dongle;          
    size_t              compile_counter;
    long                last_compile_time;
    pthread_t           thread;
    t_mtx               coder_mutex;
    
};

struct s_dongle
{
    t_mtx     dongle;
    int       dongle_id;
};

typedef enum    e_opcode
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH
}   t_opcode;

typedef enum    e_timecode
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}   t_timecode;

typedef enum    e_state
{
    COMPILE,
    DEBUG,
    REFACTOR,
    TAKE_FIRST_DONGLE,
    TAKE_SECOND_DONGLE,
    BURNOUT
}   t_state;

int	    parsing(char **argv, t_data *parse);
void    *safe_malloc(size_t size);
void    data_init(t_data *data);
void	print_error_usage(void);
void    error_exit(char *error_message);
void    safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void    safe_thread_handle(
    pthread_t *thread, void *(*foo)(void *), void* data, t_opcode opcode);
void    set_bool(t_mtx *mutex, bool *dest, bool value);
bool    get_bool(t_mtx *mutex, bool *value);
void    set_long(t_mtx *mutex, long *dest, long value);
long    get_long(t_mtx *mutex, long *value);
bool    simulation_end(t_data *data);
void    spinlock(t_data *data);
long    get_time(t_timecode timecode);
void    better_usleep(long usec, t_data *data);
void    write_status(t_state status, t_coder *coder);
void    simulation_start(t_data *data);
void    init_coder(t_data *data);
bool    all_coders_running(t_mtx *mutex, long *threads, long coder_nbr);
void    increase_long(t_mtx *mutex, long *value);
void    *monitor_data(void *data);

#endif
