/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_t_stop_program.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:43:49 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/14 16:09:38 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Main constant observer that will be checking constantly if the process should stop or not. 
void	*t_handler_stop_program(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->min_amount_meals == 0)
		return (NULL);
	//// update_sim_should_stop(table, false);
	sync_threads(table->start_meeting_at);
	while (true)
	{
		if (are_all_conditions_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
