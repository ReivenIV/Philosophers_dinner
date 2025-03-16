/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_observers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:49:13 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 15:58:28 by urlooved             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// Will check status of sim_should_stop if TRUE we should end the simulation
bool	should_sim_end(t_table *table)
{
	bool res;

	res = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_should_stop == true)						// If table->sim_should_stop is true then we output true (yes we should stop the process)
		res = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (res);
}

// Will check if any philo died in the table, print the statement and raise the flag that we should stop the simulation
bool	is_philo_dead(t_phi *philo)
{
	time_t	current_time;

	current_time = now_at();
	if ((current_time - philo->last_meal_at) >= philo->table->t_t_die)
	{
		print_statement(philo, "DIED");
		update_sim_should_stop(philo->table, true);
		pthread_mutex_unlock(&philo->phi_action_lock);
		return (true);										// yep someone died
	}
	return (false);											// all philosophers are alive. (continue the process)
}

// Will check if philos are alive & if everyone had ete the min amount of meals.
// if conditions reached == TRUE else FALSE
bool	are_all_conditions_reached(t_table *table)
{
	unsigned int	i;
	bool			amount_min_meals_reached;

	i = 0;
	amount_min_meals_reached = true;
	while (i < table->amount_philos)
	{
		pthread_mutex_lock(&table->philos[i]->phi_action_lock);
		if (is_philo_dead(table->philos[i]))
			return (true);															// Will check if a philo died or not a philo if yes stop the procees (its announced at func "is_philo_dead")
		if (table->min_amount_meals != -1)
			if (table->philos[i]->times_ate < (unsigned int)table->min_amount_meals)
				amount_min_meals_reached = false;										// if min_amount_meals not reached then we continue the process. 
		pthread_mutex_unlock(&table->philos[i]->phi_action_lock);
		i++;
	}
	if (table->min_amount_meals != -1 && amount_min_meals_reached == true)
	{
		update_sim_should_stop(table, true);
		return (true);
	}
	return (false);
}

// bool	are_all_conditions_reached(t_table *table)
// {
// 	unsigned int	i;
// 	bool			amount_min_meals_reached;

// 	if (table->min_amount_meals == -1)						// REMINDER: amount_of_meals is optional is if -1 then we loop forever.
// 		return (false);
// 	i = 0;
// 	amount_min_meals_reached = true;
// 	while (i < table->amount_philos)
// 	{
// 		pthread_mutex_lock(&table->philos[i]->phi_action_lock);
// 		if (is_philo_dead(table->philos[i]))
// 			return (true);
// 		if (table->philos[i]->times_ate < (unsigned int)table->min_amount_meals)
// 			amount_min_meals_reached = false;
// 		pthread_mutex_unlock(&table->philos[i]->phi_action_lock);
// 		i++;
// 	}
// 	if (amount_min_meals_reached == true)
// 	{
// 		update_sim_should_stop(table, true);
// 		return (true);
// 	}
// 	return (false);
// }