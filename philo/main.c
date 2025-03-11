/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:02:28 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/11 13:47:20 by urlooved         ###   ########.fr       */
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

	// TODO if only 1philo it should die automatically
		// inits: table g_mutexes, forks, array of philosophers
	table = init_table(ac, av);
	if (!table)
		exit (1);
	
	// Seeters, routines(eat, think, sleep), all processes threads / mutex activities
	//TODO eat, sleep, think time
	
	//TODO end process free all. 
	
	return (0);
}