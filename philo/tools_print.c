/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:44:32 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/12 15:01:26 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_statement(t_philo *philo, char *status)
{
	time_t	now_at;
	int		philo_id;

	pthread_mutex_lock(&philo->table->write_lock);
	if (should_sim_end(philo->table) == true)					// if end of the process we cut the acces to write in the terminal
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	now_at = get_time_in_ms() - philo->table->start_meeting_at;
	philo_id = philo->id + 1;
	if (status[0] == 'D')
		printf("%ld %d %s\n", now_at, philo_id, "died");
	else if (status[0] == 'E')
		printf("%ld %d %s\n", now_at, philo_id, "is eating");
	else if (status[0] == 'S')
		printf("%ld %d %s\n", now_at, philo_id, "is sleeping");
	else if (status[0] == 'T')
		printf("%ld %d %s\n", now_at, philo_id, "is thinking");
	else if (status[0] == 'F')
		printf("%ld %d %s\n", now_at, philo_id, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_lock);
}
