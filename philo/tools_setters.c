/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:02:02 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/10 15:37:02 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	to avoid Dead-lock and to avoid min meal amount
	to EVEN philo ids we left handed the forks. 
	EX : even philos ids "left-handed" helps:
		Philo #0 (id: 0) takes ""fork 1"" and then fork 0
		Philo #1 (id: 1) takes ""fork 1"" and then fork 2
		Philo #2 (id: 2) takes ""fork 0"" and then fork 2	
	
	""philo->fork[0] = philo->id;"" is going to be the first fork the want to 
	take. If we don't switch it everyone will try to peek their own 
	fork related to their philo id. Creating a deadlock (try it without and
	check the meals intake you will see some miss a meal at the end of the
	process. ;) )
*/
void	set_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)												// Set forks to EVEN id philos
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % philo->table->amount_philos;
	}
	else																// Set forks to ODD id philos 	
	{
		philo->fork[0] = (philo->id + 1) % philo->table->amount_philos;		
		philo->fork[1] = philo->id;
	}
}

void	set_philo_sleep(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_current_time() + sleep_time;
	while (get_current_time() < wake_up)
	{
		if ()
	}
	
}