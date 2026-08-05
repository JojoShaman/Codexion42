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
#include <sys/_pthread/_pthread_mutex_t.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <errno.h>

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
	char                *scheduler;
    t_coder             *coders;
    t_dongle            *dongles;

}	t_data;

struct s_coder
{
    int                 id;
    t_data              *coder_data;
    t_dongle            *right_dongle;          
    t_dongle            *left_dongle;          
    size_t              compile_counter;
    size_t              last_compile_time;
    pthread_t           thread;
    t_mtx               lock;
    
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

int	    parsing(char **argv, t_data *parse);
void	print_error_usage(void);
void    *init_coder();
void    error_exit(char *error_message);
void    safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void    safe_thread_handle(
    pthread_t *thread, void *(*foo)(void *), void* data, t_opcode opcode);
#endif
