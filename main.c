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

int	main(int argc, char **argv)
{
    t_data  data;
	if (argc != 9 || !parsing(argv, &data))
    {
        error_exit(USAGE);
        exit(EXIT_FAILURE);
    }
	else
	{
        data_init(&data);
        init_coder(&data);
        simulation_start(&data);
	}

	return (0);
}
