/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:02:28 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 11:50:32 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac < 5 || ac > 6)
		return (printf("wrong amount ac"));
	// parser
	if (!are_inputs_valid(ac, av))
		exit (1);

	if (av[1][0] == '1')						// in case we have only 1 philo we wait till it die. we don't init anything.
		return (usleep(nbs_atoi(av[2])), printf("%s 1 died\n", av[2]), 0); //TODO maybe.. 
	// TODO if only 1philo it should die automatically
		// inits: table g_mutexes, forks, array of philosophers
	table = init_table_philos(ac, av);
	if (!table)
		exit (1);
	
	// Seeters, routines(eat, think, sleep), all processes threads / mutex activities
	//TODO eat, sleep, think time
	
	//TODO end process free all. 
	
	return (0);
}
//! leaks when closing the process (in infinit loop mode)