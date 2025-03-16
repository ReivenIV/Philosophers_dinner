/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwebe-ir <fwebe-ir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:46:42 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 12:30:30 by fwebe-ir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// will free the struct table and all philosophers inside.
void	free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return ;
	if (table->fork_locks != NULL)
		free(table->fork_locks);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->amount_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
}

// Will free all global mutexes and philos in table
static void	free_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->amount_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->phi_action_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}

void	free_all(t_table *table)
{
	free_mutexes(table);
	free_table(table);
}
