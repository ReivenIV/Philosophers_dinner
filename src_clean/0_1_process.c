/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_1_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:58:30 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 17:59:12 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Create all mutexes and start process.
// If fail == FALSE else TRUE 
bool	begin_process(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->amount_philos)
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL, &t_handler_philo,
				table->philos[i]) != 0)
			return (printf("bp: error init thread"), free_table(table), false);
		i++;
	}
	if (table->amount_philos > 1)
	{
		if (pthread_create(&table->t_handler_stop_program, NULL,
				&t_handler_stop_program, table) != 0)
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
	if (table->amount_philos > 1)
		pthread_join(table->t_handler_stop_program, NULL);
	free_all(table);
}
