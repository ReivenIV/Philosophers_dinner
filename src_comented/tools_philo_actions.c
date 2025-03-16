/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_philo_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:37:39 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 17:15:14 by urlooved             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Reminder : &philo->table->fork_locks[philo->fork[0]]
	is the adresse of the fork mutex related to a philo_id.
*/
void	eat_sleep_process(t_phi *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_statement(philo, "Fork_0");										// take fork
	
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	print_statement(philo, "Fork_1");										// take fork
	print_statement(philo, "Eating");

	pthread_mutex_lock(&philo->phi_action_lock);
	philo->last_meal_at = now_at();											// update last_meal_at
	pthread_mutex_unlock(&philo->phi_action_lock);
	
	set_phi_to("Eat", philo);												// start action Eating

	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);		// free fork
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);		// free fork
	
	print_statement(philo, "Sleeping");										// after eating and freeing forks start action "sleep"								
	set_phi_to("Sleep", philo);
}

// At the begining of the process in case amount_philos the one not eating will start thinking from the begining
void 	start_think_even(t_phi *philo)
{
	print_statement(philo, "Thinking");
	set_phi_to("Think", philo);
}
//	t = table || p = philosopher. || lma = last_meal_at  (i needed spaces sorry for that one)
void	think_process(t_table *t, t_phi *p, time_t lma)
{
	time_t	t_t;

	pthread_mutex_lock(&p->phi_action_lock);
	if (p->table->amount_philos % 2 == 0)
	{
		if (t->t_t_die - (t->t_t_eat + t->t_t_sleep) <= 20)					// In case time to think is really small related to time to die (<=20 i choose to put it to 0 to avoid risk)
			t_t = 0;
		else
			t_t = (t->t_t_die - (now_at() - lma)) * 0.9;					// in case the amount to think is big i choose to take only 90% of it. To avoid risk.
	}
	if (p->table->amount_philos % 2 != 0)
	{
		if (t->t_t_die - (t->t_t_eat + t->t_t_sleep) <= 400)
			t_t = (t->t_t_die - (now_at() - lma) - t->t_t_eat) * 0.40;
		else
			t_t = (t->t_t_die - (now_at() - lma) - t->t_t_eat) * 0.75;
		printf("t_t = %li - - %li\n", t_t, t->t_t_die - (now_at() - lma) - t->t_t_eat);
	}
	if (t_t < 0)
		t_t = 0;
	t->t_t_think = t_t;	
	pthread_mutex_unlock(&p->phi_action_lock);
	print_statement(p, "THINKING");

	set_phi_to("Think", p);
}

void	*wait_till_die(t_phi *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_statement(philo, "Fork_0");
	set_phi_to("Die", philo);
	print_statement(philo, "Died");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}
