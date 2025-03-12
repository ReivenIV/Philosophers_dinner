/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:46:06 by rita          #+#    #+#             */
/*   Updated: 2022/09/10 16:13:10 by rita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!are_valid_input(ac, av))
		return (EXIT_FAILURE);
	if (av[1][0] == '1')						// in case we have only 1 philo we wait till it die. we don't init anything.
	{
		usleep(nbs_atoi(av[2]));
		printf("%s 1 died\n", av[2]);
		return (EXIT_SUCCESS);
	}
	table = init_table(ac, av);
	if (!table)
		return (EXIT_FAILURE);
	if (!begin_process(table))
		return (EXIT_FAILURE);
	end_process(table);
	return (EXIT_SUCCESS);
}
