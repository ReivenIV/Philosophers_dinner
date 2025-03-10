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

/* start_simulation:
*	Launches the simulation by creating a grim reaper thread as well as
*	one thread for each philosopher.
*	Returns true if the simulation was successfully started, false if there
*	was an error. 
*/
static bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->start_meeting_at = get_time_in_ms() + (table->amount_philos * 2 * 10);
	i = 0;
	while (i < table->amount_philos)
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL,	&philosopher, table->philos[i]) != 0)
			return (printf("SS: error init threat"), free_table(table), false);	
		i++;
	}
	if (table->amount_philos > 1)
	{
		if (pthread_create(&table->t_stop_program, NULL, &t_stop_program, table) != 0)
			return (printf("SS: error init threat"), free_table(table), false);
	}
	return (true);
}

/* stop_simulation:
*	Waits for all threads to be joined then destroys mutexes and frees
*	allocated memory.
*/
static void	stop_simulation(t_table	*table)
{
	unsigned int	i;

	i = 0;
	while (i < table->amount_philos)
	{
		pthread_join(table->philos[i]->thread_id, NULL);
		i++;
	}
	if (table->amount_philos > 1)
		pthread_join(table->t_stop_program, NULL);
	if (DEBUG_FORMATTING == true && table->min_amount_meals != -1)
		write_outcome(table);
	free_mutexes(table);
	free_table(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!are_valid_input(ac, av))
		return (EXIT_FAILURE);
	table = init_table(ac, av, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	stop_simulation(table);
	return (EXIT_SUCCESS);
}
