/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_1_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:58:30 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/14 14:35:29 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Create all mutexes and start process.
// If fail == FALSE else TRUE 
bool	begin_process(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->amount_philos)	// We create each thread for each philo and we put them into work.
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL, &t_handler_philo, table->philos[i]) != 0)
			return (printf("bp: error init thread"), free_table(table), false);
		i++;
	}

	if (table->amount_philos > 1)		// We need these condition because for only 1 philo will not do the same process.
	{
		if (pthread_create(&table->t_handler_stop_program, NULL, &t_handler_stop_program, table) != 0)	// we create the thread t_handler_stop_program that will be constantly checking if the the conditions are reached (DIED or min_amount_meals reached.)
			return (printf("bp: error init threat"), free_table(table), false);
	}
	return (true);
}
// Wait till all threads & mutexes are join then free all.
void	end_process(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->amount_philos)
	{
		pthread_join(table->philos[i]->thread_id, NULL);
		i++;
	}
	if (table->amount_philos > 1)				// REMINDER: with philo 1 we don't have t_handler_stop_program.
		pthread_join(table->t_handler_stop_program, NULL);
	free_all(table); 							// Will free mutexes(philos, globals), table
}