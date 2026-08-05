/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: srosu <srosu@student.42belgium.be>        #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/31 17:16:25 by srosu            #+#    #+#              */
/*   Updated: 2026/07/31 19:56:23 by srosu           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <_time.h>
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
    printf("test");
    t_data	parse;
    t_data  data;
	if (argc != 9 || !parsing(argv, &parse))
    {
		// print_error_usage();
        error_exit(USAGE);
        exit(EXIT_FAILURE);
    }
	else
	{
		printf("%lu\n", parse.number_of_coders);
		printf("%lu\n", parse.time_to_burnout);
		printf("%lu\n", parse.time_to_compile);
		printf("%lu\n", parse.time_to_debug);
		printf("%lu\n", parse.time_to_refactor);
		printf("%lu\n", parse.number_of_compiles_required);
		printf("%lu\n", parse.dongle_cooldown);
		printf("%s\n", parse.scheduler);
	}

	return (0);
}
