/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:44:32 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/12 10:50:23 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_statement(t_philo *philo, char *status)
{
	time_t	now_at;
	int		philo_id;

	pthread_mutex_lock(&philo->table->write_lock);
	if (should_sim_end(philo->table) == true)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	now_at = get_current_time() - philo->table->start_meeting_at;
	philo_id = philo->id + 1;
	if (ft_strcmp(status, "DIED") == 0)
		printf("%ld %d %s\n", now_at, philo_id, "died");
	else if (ft_strcmp(status, "EATING") == 0)
		printf("%ld %d %s\n", now_at, philo_id, "is eating");
	else if (ft_strcmp(status, "SLEEPING") == 0)
		printf("%ld %d %s\n", now_at, philo_id, "is sleeping");
	else if (ft_strcmp(status, "THINKING") == 0)
		printf("%ld %d %s\n", now_at, philo_id, "is thinking");
	else if (ft_strcmp(status, "FORK_0") == 0 || ft_strcmp(status, "FORK_1") == 0)
		printf("%ld %d %s\n", now_at, philo_id, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_lock);
}