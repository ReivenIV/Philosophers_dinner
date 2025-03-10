/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:38:28 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/10 13:14:06 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// Will init amount of forks mutexes. (amount philos == amount forks)
// return array of forks or NULL. 
pthread_mutex_t *init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->amount_philos);
	if (!forks)
		return (printf("IF: error malloc"), NULL);
	i = 0;
	while (i < table->amount_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (printf("IF: error mutexing"), NULL);
		i++;
	}
	return (forks);
}
// Will fill the array philosopher and init their values (table, id, time_ate)
// 

t_philo	**init_philos(t_table *table)
{
	t_philo			**arr_philo;
	unsigned int	i;

	arr_philo = malloc(sizeof(t_philo) * table->amount_philos);
	if (!arr_philo)
		return (printf("IP: error malloc"), NULL);
	i = 0;
	while (i < table->amount_philos)
	{
		arr_philo[i] = malloc(sizeof(t_philo));					// Will create 1 t_philo per loop
		if (!arr_philo[i])
			return (printf("IP: error malloc"), NULL);
		if (pthread_mutex_init(&arr_philo[i]->meal_time_lock, 0) != 0)
			return (printf("IP: error mutex"), NULL);
		arr_philo[i]->table = table;
		arr_philo[i]->id = i;
		arr_philo[i]->times_ate = 0;
		assign_forks(arr_philo[i]);
		i++;
	}
	return (arr_philo);
}
