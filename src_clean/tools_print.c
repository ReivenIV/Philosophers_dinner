/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:44:32 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 17:59:12 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_statement(t_phi *philo, char *status)
{
	time_t	process_at;
	int		philo_id;

	pthread_mutex_lock(&philo->table->write_lock);
	if (should_sim_end(philo->table) == true)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	process_at = now_at() - philo->table->start_meeting_at;
	philo_id = philo->id + 1;
	if (status[0] == 'D')
		printf("%ld %d %s\n", process_at, philo_id, "died");
	else if (status[0] == 'E')
		printf("%ld %d %s\n", process_at, philo_id, "is eating");
	else if (status[0] == 'S')
		printf("%ld %d %s\n", process_at, philo_id, "is sleeping");
	else if (status[0] == 'T')
		printf("%ld %d %s\n", process_at, philo_id, "is thinking");
	else if (status[0] == 'F')
		printf("%ld %d %s\n", process_at, philo_id, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_lock);
}
