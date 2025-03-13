/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_handler_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:25:09 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 15:56:58 by urlooved         ###   ########.fr       */
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
void	*t_handler_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->min_amount_meals == 0)
		return (NULL);
	sim_start_delay(philo->table->start_meeting_at);
	if (philo->table->amount_philos == 1)
		return (wait_till_die(philo));
	else if (philo->id % 2)
	{
		if (philo->table->amount_philos % 2 == 0)
			start_think_even(philo);
		else
			think_routine(philo);
	}
	else if (philo->table->amount_philos % 2 != 0 && philo->id == philo->table->amount_philos - 1)
		think_routine(philo);
		
	while (should_sim_end(philo->table) == false)
	{
		eat_sleep_process(philo);
		think_routine(philo);
	}
	return (NULL);
}
