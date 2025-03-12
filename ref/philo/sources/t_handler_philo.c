/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_handler_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:25:09 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/12 15:40:46 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* philosopher:
*	The philosopher thread routine. The philosopher must eat, sleep
*	and think. In order to avoid conflicts between philosopher threads,
*	philosophers with an even id start by thinking, which delays their
*	meal time by a small margin. This allows odd-id philosophers to
*	grab their forks first, avoiding deadlocks.
*/
void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->min_amount_meals == 0)
		return (NULL);
	// // pthread_mutex_lock(&philo->meal_time_lock);
	// // philo->last_meal_at = philo->table->start_meeting_at;
	// // pthread_mutex_unlock(&philo->meal_time_lock);


	sim_start_delay(philo->table->start_meeting_at);
	// // if (philo->table->time_to_die == 0)					//! These should be at the parser stage
	// // 	return (NULL);										//! These should be at the parser stage

	// no need part ------ we handle is in main.c
	if (philo->table->amount_philos == 1)
		return (one_philo_process(philo));
	// -------------------
	else if (philo->id % 2)
		think_routine(philo, true);
	while (should_sim_end(philo->table) == false)
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
	}
	return (NULL);
}