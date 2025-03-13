/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_1_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:22:32 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 16:04:08 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* begin_process:
*	Launches the simulation by creating a grim reaper thread as well as
*	one thread for each philosopher.
*	Returns true if the simulation was successfully started, false if there
*	was an error. 
*/
bool	begin_process(t_table *table)
{
	unsigned int	i;

	// // table->start_meeting_at = get_time_in_ms() + (table->amount_phis * 2 * 10);
	i = 0;
	while (i < table->amount_phis)
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL,	&t_handler_philo, table->philos[i]) != 0)
			return (printf("SS: error init threat"), free_table(table), false);	
		i++;
	}

	if (table->amount_phis > 1)
	{
		if (pthread_create(&table->t_stop_program, NULL, &t_stop_program, table) != 0)
			return (printf("SS: error init threat"), free_table(table), false);
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
	while (i < table->amount_phis)
	{
		pthread_join(table->philos[i]->thread_id, NULL);
		i++;
	}
	if (table->amount_phis > 1)
		pthread_join(table->t_stop_program, NULL);
	if (DEBUG_FORMATTING == true && table->min_amount_meals != -1)
		write_outcome(table);
	free_mutexes(table);
	free_table(table);
}