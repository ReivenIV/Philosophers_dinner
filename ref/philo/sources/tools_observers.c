/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_observers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:44:34 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/11 14:11:12 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



/* are_all_conditions_reached:
*	Checks each philosopher to see if one of two end conditions
*	has been reached. Stops the simulation if a philosopher needs
*	to be killed, or if every philosopher has eaten enough.
*	Returns true if an end condition has been reached, false if not.
*/
bool	are_all_conditions_reached(t_table *table)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->amount_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->min_amount_meals != -1) //!
			if (table->philos[i]->times_ate	< (unsigned int)table->min_amount_meals)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (table->min_amount_meals != -1 && all_ate_enough == true)
	{
		set_sim_should_stop_flag(table, true);
		return (true);
	}
	return (false);
}

/* should_sim_end:
*	Checks whether the simulation is at an end. The stop flag
*	is protected by a mutex lock to allow any thread to check
*	the simulation status without conflict.
*	Returns true if the simulation stop flag is set to true,
*	false if the flag is set to false. 
*/
bool	should_sim_end(t_table *table)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_should_stop == true)
		res = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (res);
}