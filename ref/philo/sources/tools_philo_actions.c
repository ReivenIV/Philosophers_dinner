/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_philo_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:12:00 by rita              #+#    #+#             */
/*   Updated: 2025/03/12 15:26:52 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* eat_sleep_routine:
*	When a philosopher is ready to eat, he will wait for his fork mutexes to
*	be unlocked before locking them. Then the philosopher will eat for a certain
*	amount of time. The time of the last meal is recorded at the beginning of
*	the meal, not at the end, as per the subject's requirements.
*/
void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_statement(philo, "FORK_0");

	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	print_statement(philo, "FORK_1");
	print_statement(philo, "EATING");
	
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_at = get_time_in_ms();

	pthread_mutex_unlock(&philo->meal_time_lock);
	set_philo_to(philo->table, philo->table->time_to_eat);
	if (should_sim_end(philo->table) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	print_statement(philo, "SLEEPING");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	set_philo_to(philo->table, philo->table->time_to_sleep);
}

/* think_routine:
*	Once a philosopher is done sleeping, he will think for a certain
*	amount of time before starting to eat again.
*	The time_to_think is calculated depending on how long it has been
*	since the philosopher's last meal, the time_to_eat and the time_to_die
*	to determine when the philosopher will be hungry again.
*	This helps stagger philosopher's eating routines to avoid forks being
*	needlessly monopolized by one philosopher to the detriment of others.
*/
void	think_routine(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->table->time_to_die - (get_time_in_ms() - philo->last_meal_at) - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		print_statement(philo, "THINKING");
	set_philo_to(philo->table, time_to_think);
}

/* lone_philo_routine:
*	This routine is invoked when there is only a single philosopher.
*	A single philosopher only has one fork, and so cannot eat. The
*	philosopher will pick up that fork, wait as long as time_to_die and die.
*	This is a separate routine to make sure that the thread does not get
*	stuck waiting for the second fork in the eat routine.
*/
void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_statement(philo, "FORK_0");
	set_philo_to(philo->table, philo->table->time_to_die);
	print_statement(philo, "DIED");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}


