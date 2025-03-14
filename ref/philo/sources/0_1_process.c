/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_1_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:22:32 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/14 12:28:20 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* begin_process:
*	Launches the simulation by creating t_handler_stop_program thread as well as
*	one thread for each philosopher.
*	Returns true if the simulation was successfully started, false if there
*	was an error. 
*/
bool	begin_process(t_table *table)
{
	unsigned int	i;

	// // table->start_meeting_at = now_at() + (table->amount_philos * 2 * 10);
	i = 0;
	while (i < table->amount_philos)
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL,	&t_handler_philo, table->philos[i]) != 0)
			return (printf("bp ER: thread philos"), free_table(table), false);
		i++;
	}

	if (table->amount_philos > 1)
	{
		if (pthread_create(&table->t_handler_stop_program, NULL, &t_handler_stop_program, table) != 0)
			return (printf("bp: error init threat"), free_table(table), false);
	}
	return (true);
}

/* end_process:
*	Waits for all threads to be joined then destroys mutexes and frees
*	allocated memory.
*/
void	end_process(t_table	*table)
{
	unsigned int	i;

	i = 0;
	while (i < table->amount_philos)
	{
		pthread_join(table->philos[i]->thread_id, NULL);
		i++;
	}
	if (table->amount_philos > 1)
		pthread_join(table->t_handler_stop_program, NULL);
	if (DEBUG_FORMATTING == true && table->min_amount_meals != -1)
		write_outcome(table);
	// // free_mutexes(table);
	// // free_table(table);
	free_all(table);  // Will free mutexes(philos, globals), table
}