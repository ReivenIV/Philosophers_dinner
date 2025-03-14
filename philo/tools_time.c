/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:40:00 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/14 12:28:20 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philo.h"

// Will get current time in ms
time_t	now_at(void)
{
	struct timeval		t_v;

	gettimeofday(&t_v, NULL);
	return ((t_v.tv_sec * 1000) + (t_v.tv_usec / 1000));
}

// test : now_at
// // int main(void)
// // {
// //     return (printf("Current time in ms: %ld\n", now_at()), 0);
// // }

/*
- Will delay the simulation like that all thread are synchronized 
- This ensures t_handler_stop_program thread is synchronized with 
	the philosopher threads.
*/
void	sim_start_delay(time_t start_meeting_at)
{
	while (now_at() < start_meeting_at)
		continue ;									// will loop until the condition is reached
}