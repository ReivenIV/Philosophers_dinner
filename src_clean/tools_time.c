/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwebe-ir <fwebe-ir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:40:00 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 12:56:07 by fwebe-ir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Will get current time in ms
time_t	now_at(void)
{
	struct timeval	t_v;

	gettimeofday(&t_v, NULL);
	return ((t_v.tv_sec * 1000) + (t_v.tv_usec / 1000));
}

/*
- Will delay the simulation like that all thread are synchronized 
- This ensures t_handler_stop_program thread is synchronized with 
	the philosopher threads.
*/
void	sync_threads(time_t start_meeting_at)
{
	while (now_at() < start_meeting_at)
		continue ;
}
