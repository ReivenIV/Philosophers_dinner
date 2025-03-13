/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_observers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:44:34 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 17:14:42 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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


// will check if the meal surpasses the "t_t_die". If yes we announce the death of a philo. 
bool	is_philo_dead(t_phi *philo)
{
	time_t	current_time;

	current_time = get_time_in_ms();
	if ((current_time - philo->last_meal_at) >= philo->table->time_to_die)
	{
		print_statement(philo, "DIED");
		update_sim_should_stop(philo->table, true);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

/* are_all_conditions_reached:
*	Checks each philosopher to see if one of two end conditions
*	has been reached. Stops the simulation if a philosopher needs
*	to be killed, or if every philosopher has eaten enough.
*	Returns true if an end condition has been reached, false if not.
*/

bool	are_all_conditions_reached(t_table *table)
{
	unsigned int	i;
	bool			amount_min_meals_reached;

	if (table->min_amount_meals == -1)		// REMINDER: amount_of_meals is optional
		return (false);
	amount_min_meals_reached = true;
	i = 0;
	while (i < table->amount_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (is_philo_dead(table->philos[i]))
			return (true);
		if (table->philos[i]->times_ate	< (unsigned int)table->min_amount_meals)
			amount_min_meals_reached = false;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (amount_min_meals_reached == true)
	{
		update_sim_should_stop(table, true);
		return (true);
	}
	return (false);
}

/* t_stop_program:
*	The t_stop_program thread's routine. Checks if a philosopher must
*	be killed and if all philosophers ate enough. If one of those two
*	end conditions are reached, it stops the simulation.
*/
//TODO create a handler and a extra file.
void	*t_stop_program(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->min_amount_meals == 0)
		return (NULL);
	//// update_sim_should_stop(table, false);
	sim_start_delay(table->start_meeting_at);
	while (true)
	{
		if (are_all_conditions_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}