/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:40:00 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/10 11:35:05 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philo.h"

// Will get current time in ms
time_t	get_current_time(void)
{
	struct timeval		t_v;

	gettimeofday(&t_v, NULL);
	return ((t_v.tv_sec * 1000) + (t_v.tv_usec / 1000));
}

// test : get_current_time
// // int main(void)
// // {
// //     return (printf("Current time in ms: %ld\n", get_current_time()), 0);
// // }

/*
- Will delay the simulation like that all thread are synchronized 
- This ensures t_stop_program thread is synchronized with 
	the philosopher threads.
*/
void	sim_start_delay(time_t start_meeting_at)
{
	while (get_current_time() < start_meeting_at)
		continue ;									// will loop until the condition is reached
}