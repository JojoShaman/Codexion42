#include "../codexion.h"

static int is_data_valid(char **argv)
{
    int	i = 1;
	int	j;

	while (i < 8)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		if (atoi(argv[i]) < 0)
			return (0);
		i++;
	}
    return 1;
}

int	parsing(char **argv, t_data *parse)
{
    if (!is_data_valid(argv))
        return (0);
	parse->number_of_coders = atoi(argv[1]);
	parse->time_to_burnout = atoi(argv[2]);
	parse->time_to_compile = atoi(argv[3]);
	parse->time_to_debug = atoi(argv[4]);
	parse->time_to_refactor = atoi(argv[5]);
	parse->number_of_compiles_required = atoi(argv[6]);
	parse->dongle_cooldown = atoi(argv[7]);
	if (!strcmp(argv[8], "FIFO") || !strcmp(argv[8], "fifo"))
		parse->scheduler = "fifo";
	else if (!strcmp(argv[8], "EDF") || !strcmp(argv[8], "edf"))
		parse->scheduler = "edf";
	else
		return (0);
	return (1);
}