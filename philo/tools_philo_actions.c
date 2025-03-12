/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_philo_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:37:39 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/12 16:20:02 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*one_philo_process(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
// 	print_statement(philo, "Fork_0");
// 	set_philo_to(philo->table, philo->table->t_t_die);
// 	print_statement(philo, "Died");
// 	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
// 	return (NULL);
// }

void	eat_sleep_process(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_statement(philo, "Fork_0");
	
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	print_statement(philo, "Fork_1");
	print_statement(philo, "Eating");

	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_at = get_current_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	
	set_philo_to(philo->table, philo->table->t_t_eat);

	if (should_sim_end(philo->table) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	print_statement(philo, "Sleeping");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	set_philo_to(philo->table, philo->table->t_t_sleep);
}

void	think_routine(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->table->t_t_die - (get_current_time() - philo->last_meal_at) - philo->table->t_t_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		print_statement(philo, "Thinking");
	set_philo_to(philo, "Thinking");
}

