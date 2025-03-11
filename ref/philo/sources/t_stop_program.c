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
