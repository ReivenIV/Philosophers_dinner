/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_philo_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:37:39 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 16:04:08 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	eat_sleep_process(t_phi *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_statement(philo, "Fork_0");										// take fork
	
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	print_statement(philo, "Fork_1");										// take fork
	print_statement(philo, "Eating");

	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_at = get_current_time();								// update last_meal_at
	pthread_mutex_unlock(&philo->meal_time_lock);
	
	set_phi_to("Eat", philo->table, philo->table->t_t_eat, philo);		// start action Eating

	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);		// free fork
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);		// free fork
	
	print_statement(philo, "Sleeping");										// after eating and freeing forks start action "sleep"								
	set_phi_to("Sleep", philo->table, philo->table->t_t_sleep, philo);
}

// At the begining of the process in case amount_phis the one not eating will start thinking from the begining
void 	start_think_even(t_phi *philo)
{
	print_statement(philo, "Thinking");
	set_phi_to("Think", philo->table, philo->table->t_t_eat + 10, philo);
}

void	think_routine(t_phi *philo)
{
	time_t	t_t_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	if (philo->table->amount_phis % 2 == 0)
		t_t_think = (philo->table->t_t_die - (get_current_time() - philo->last_meal_at) - philo->table->t_t_eat) * 0.98;	// t_t_think: for Even philos, we will max the possible amount of thinking
	else
		t_t_think = (philo->table->t_t_die - (get_time_in_ms() - philo->last_meal_at) - philo->table->t_t_eat) / 2;			// t_t_think: for ODD amount philos You will have 1 philo waiting a lot and we don't want him to die. Is for that the t_t_think / 2.
	pthread_mutex_unlock(&philo->meal_time_lock);

	if (t_t_think < 0)																										// In case t_t_think is negative we put it to 0.
		t_t_think = 0;

	print_statement(philo, "Thinking");
	
	if ((philo->table->amount_phis % 2 != 0 && philo->id == philo->table->amount_phis - 2))			// in case not amount of philo == ODD, the last ODD will think 50 more. 
		set_phi_to("Think", philo->table, t_t_think + 50, philo);
	else 
		set_phi_to("Think", philo->table, t_t_think, philo);
}

void	*wait_till_die(t_phi *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_statement(philo, "Fork_0");
	set_phi_to("Die", philo->table, philo->table->t_t_die, philo);
	print_statement(philo, "Died");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}