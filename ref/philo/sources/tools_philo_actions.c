/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_philo_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:12:00 by rita              #+#    #+#             */
/*   Updated: 2025/03/14 10:54:31 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* wait_till_die:
*	When a philosopher is ready to eat, he will wait for his fork mutexes to
*	be unlocked before locking them. Then the philosopher will eat for a certain
*	amount of time. The time of the last meal is recorded at the beginning of
*	the meal, not at the end, as per the subject's requirements.
*/


void	eat_sleep_process(t_phi *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_statement(philo, "FORK_0");
	
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	print_statement(philo, "FORK_1");
	print_statement(philo, "EATING");
	
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_at = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);

	set_phi_to("Eat", philo);
	
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	
	print_statement(philo, "SLEEPING");
	set_phi_to("Sleep",philo);
}

// ? ---------------------------------------------------------------------------------
// ? ---------------------------------------------------------------------------------
/* think_process:
*	Once a philosopher is done sleeping, he will think for a certain
*	amount of time before starting to eat again.
*	The time_to_think is calculated depending on how long it has been
*	since the philosopher's last meal, the time_to_eat and the time_to_die
*	to determine when the philosopher will be hungry again.
*	This helps stagger philosopher's eating routines to avoid forks being
*	needlessly monopolized by one philosopher to the detriment of others.
*/

void	start_think_even(t_phi *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);

	time_to_think = philo->table->time_to_eat + 10;

	philo->table->time_to_think = time_to_think;
	pthread_mutex_unlock(&philo->meal_time_lock);
	
	print_statement(philo, "THINKING");
	set_phi_to("Think", philo);
}

void	think_process(t_phi *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	if (philo->table->amount_philos % 2 == 0)
		time_to_think = (philo->table->time_to_die - (get_time_in_ms() - philo->last_meal_at)) * 0.98;
	else 
		time_to_think = (philo->table->time_to_die - (get_time_in_ms() - philo->last_meal_at) - philo->table->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;

	philo->table->time_to_think = time_to_think;
	pthread_mutex_unlock(&philo->meal_time_lock);
	

	print_statement(philo, "THINKING");

	if ((philo->table->amount_philos % 2 != 0 && philo->id == philo->table->amount_philos - 2))
	{
		philo->table->time_to_think = time_to_think + 50;
		set_phi_to("Think", philo);
	}
	else 
		set_phi_to("Think", philo);
}

/* wait_till_die:
*	This routine is invoked when there is only a single philosopher.
*	A single philosopher only has one fork, and so cannot eat. The
*	philosopher will pick up that fork, wait as long as time_to_die and die.
*	This is a separate routine to make sure that the thread does not get
*	stuck waiting for the second fork in the eat routine.
*/

/*
	1 philo = Will die 
	No need for lock/unlock beceause we have only 1 thread in the proces
		is not possible to create a data race.
*/
void	*wait_till_die(t_phi *philo) // done 
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_statement(philo, "FORK_0");
	set_phi_to("Die", philo);
	print_statement(philo, "DIED");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}
