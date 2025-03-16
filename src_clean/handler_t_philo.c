/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_t_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwebe-ir <fwebe-ir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:11:10 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 12:43:12 by fwebe-ir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*t_handler_philo(void *data)
{
	t_phi	*philo;

	philo = (t_phi *)data;
	sync_threads(philo->table->start_meeting_at);
	if (philo->table->amount_philos == 1)
		return (wait_till_die(philo), NULL);
	else if (philo->id % 2)
	{
		if (philo->table->amount_philos % 2 == 0)
			start_think_even(philo);
		else
			think_process(philo->table, philo);
	}
	else if (philo->table->amount_philos % 2 != 0
		&& philo->id == philo->table->amount_philos - 1)
		think_process(philo->table, philo);
	while (should_sim_end(philo->table) == false)
	{
		eat_sleep_process(philo);
		think_process(philo->table, philo);
	}
	return (NULL);
}
