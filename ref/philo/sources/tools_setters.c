/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:57:37 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/10 17:08:33 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* set_sim_should_stop_flag:
*	Sets the simulation stop flag to true or false. Only the grim
*	reaper thread can set this flag. If the simulation stop flag is
*	set to true, that means the simulation has met an end condition.
*/
void	set_sim_should_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
		table->sim_should_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}


/* set_forks:
*	Assigns two fork ids to each philosopher. Even-numbered philosophers
*	get their fork order switched. This is because the order in which
*	philosophers take their forks matters.
*
*	For example with 3 philos:
*		Philo #0 (id: 0) will want fork 0 and fork 1
*		Philo #1 (id: 1) will want fork 1 and fork 2
*		Philo #2 (id: 2) will want fork 2 and fork 0
*	If philo #0 takes fork 0, philo #1 takes fork 1 and philo #2 takes fork 2,
*	there is a deadlock. Each will be waiting for their second fork which is
*	in use by another philo.
*
*	Making even id philos "left-handed" helps:
*		Philo #0 (id: 0) takes fork 1 and then fork 0
*		Philo #1 (id: 1) takes fork 1 and then fork 2
*		Philo #2 (id: 2) takes fork 0 and then fork 2
*	Now, philo #0 takes fork 1, philo #2 takes fork 0 and philo #1 waits patiently.
*	Fork 2 is free for philo #2 to take, so he eats. When he is done philo #0 can
*	take fork 0 and eat. When he is done, philo #2 can finally get fork 1 and eat.
*/

// TODO in setters
void	set_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)												// set forks to philo even
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % philo->table->amount_philos;
	}
	else
	{
		philo->fork[0] = (philo->id + 1) % philo->table->amount_philos;
		philo->fork[1] = philo->id;
	}
}

/* philo_sleep:
*	Pauses the philosopher thread for a certain amount of time in miliseconds.
*	Periodically checks to see if the simulation has ended during the sleep
*	time and cuts the sleep short if it has.
*/
void	set_philo_sleep(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (should_sim_end(table))
			break ;
		usleep(100);
	}
}

