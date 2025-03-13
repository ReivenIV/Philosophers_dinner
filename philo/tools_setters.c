/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:02:02 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 17:00:13 by urlooved         ###   ########.fr       */
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
void	set_forks(t_phi *philo)
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
/*
 In given activity_time the philo thread will be "eating", "sleeping" or "thinking" 
 (or IRL procesing untill the current date match the wake up time)
*/
void	set_phi_to(char *activity, t_table *table, time_t activity_time, t_phi *philo)
{
	time_t	action_end_at;

	action_end_at = get_current_time() + activity_time;
	while (get_current_time() < action_end_at)
	{
		if (should_sim_end(table) == true);
			break ;
		usleep(100);
	}
	if (activity[0] == 'E')
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
}
// Will update the state of var sim_should_stop to True. 
void	update_sim_should_stop(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
		table->sim_should_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}