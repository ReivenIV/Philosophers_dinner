/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:07:22 by rita          #+#    #+#             */
/*   Updated: 2022/07/08 13:30:09 by rita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* get_time_in_ms:
*	Gets the current time in miliseconds since the Epoch (1970-01-01 00:00:00).
*	Returns the time value.
*/
time_t	get_time_in_ms(void)
{
	struct timeval		t_v;

	gettimeofday(&t_v, NULL);
	return ((t_v.tv_sec * 1000) + (t_v.tv_usec / 1000));
}



/* sim_start_delay:
*	Waits for a small delay at the beginning of each threads execution
*	so that all threads start at the same time with the same start time
*	reference. This ensures t_handler_stop_program thread is synchronized with
*	the philosopher threads.
*/
void	sim_start_delay(time_t start_meeting_at)
{
	while (get_time_in_ms() < start_meeting_at)
		continue ;
}
