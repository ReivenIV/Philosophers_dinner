/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_t_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:11:10 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/14 16:11:20 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*t_handler_philo(void *data)
{
	t_phi	*philo;

	philo = (t_phi *)data;										// cast
	sync_threads(philo->table->start_meeting_at);				// Sync threads others way you can have threads starting at -something_ms
	if (philo->table->amount_philos == 1)						// 1 philo process
		return (wait_till_die(philo), NULL);
	else if (philo->id % 2)										// All "EVEN" phi_ids will think by default 
	{
		if (philo->table->amount_philos % 2 == 0)
			start_think_even(philo);
		else
			think_process(philo->table, philo);
	}
	else if (philo->table->amount_philos % 2 != 0 && philo->id == philo->table->amount_philos - 1)	// Only for ODD amount of philos. The last one will think by default 
		think_process(philo->table, philo);
	while (should_sim_end(philo->table) == false)				// The not thinking philos will start eating. Then the proces will follow naturally. 
	{
		eat_sleep_process(philo);
		think_process(philo->table, philo);
	}
	return (NULL);												// Till should_sim_end == true we loop.
}
