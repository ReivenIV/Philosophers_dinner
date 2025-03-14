/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_handler_stop_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:54:52 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 17:55:07 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* t_handler_stop_program:
*	The t_handler_stop_program thread's routine. Checks if a philosopher must
*	be killed and if all philosophers ate enough. If one of those two
*	end conditions are reached, it stops the simulation.
*/
//TODO create a handler and a extra file.
void	*t_handler_stop_program(void *data)
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