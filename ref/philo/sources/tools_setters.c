/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:57:37 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 16:04:08 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* update_sim_should_stop:
*	Sets the simulation stop flag to true or false. Only the grim
*	reaper thread can set this flag. If the simulation stop flag is
*	set to true, that means the simulation has met an end condition.
*/
void	update_sim_should_stop(t_table *table, bool state)
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

void	set_forks(t_phi *philo)
{
	if (philo->id % 2 == 0)												// set forks to philo even
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % philo->table->amount_phis;
	}
	else
	{
		philo->fork[0] = (philo->id + 1) % philo->table->amount_phis;
		philo->fork[1] = philo->id;
	}
}

/* philo_sleep:
*	Pauses the philosopher thread for a certain amount of time in miliseconds.
*	Periodically checks to see if the simulation has ended during the sleep
*	time and cuts the sleep short if it has.
*/
//TODO Maybe it should be a BOOL 
void	set_phi_to(char *activity, t_table *table, time_t activity_time, t_phi *philo)
{
	time_t	action_end_at;

	action_end_at = get_time_in_ms() + activity_time;
	while (get_time_in_ms() < action_end_at)
	{
		if (should_sim_end(table) == true)
			break ;
		usleep(100);
	}
	if (activity[0] == 'E')
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;		//! Problem here is not waiting all the time till the end of the eating process at the end.  
		////printf("times_ate: %i, P_ID: %i\n", philo->times_ate, philo->id);
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
}

