/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_stop_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:00:18 by rita          #+#    #+#             */
/*   Updated: 2022/09/10 15:05:19 by rita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"





/* kill_philo:
*	Checks if the philosopher must be killed by comparing the
*	time since the philosopher's last meal and the time_to_die parameter.
*	If it is time for the philosopher to die, sets the simulation stop
*	flag and displays the death status.
*	Returns true if the philosopher has been killed, false if not.
*/
static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal_at) >= philo->table->time_to_die)
	{
		set_sim_should_stop_flag(philo->table, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

/* end_condition_reached:
*	Checks each philosopher to see if one of two end conditions
*	has been reached. Stops the simulation if a philosopher needs
*	to be killed, or if every philosopher has eaten enough.
*	Returns true if an end condition has been reached, false if not.
*/
static bool	end_condition_reached(t_table *table)
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
		if (table->min_amount_meals != -1)
			if (table->philos[i]->times_ate
				< (unsigned int)table->min_amount_meals)
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

/* t_stop_program:
*	The t_stop_program thread's routine. Checks if a philosopher must
*	be killed and if all philosophers ate enough. If one of those two
*	end conditions are reached, it stops the simulation.
*/
void	*t_stop_program(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->min_amount_meals == 0)
		return (NULL);
	set_sim_should_stop_flag(table, false);
	sim_start_delay(table->start_meeting_at);
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
