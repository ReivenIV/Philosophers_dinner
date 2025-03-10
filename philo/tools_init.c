/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:38:28 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/10 14:00:42 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// Will init amount of forks mutexes. (amount philos == amount forks)
// return array of forks or NULL. 
static pthread_mutex_t	*init_forks(t_table *table)
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

static t_philo	**init_philos(t_table *table)
{
	t_philo			**arr_philos;
	unsigned int	i;

	arr_philos = malloc(sizeof(t_philo) * table->amount_philos);
	if (!arr_philos)
		return (printf("IP: error malloc"), NULL);
	i = 0;
	while (i < table->amount_philos)
	{
		arr_philos[i] = malloc(sizeof(t_philo));					// Will create 1 t_philo per loop
		if (!arr_philos[i])
			return (printf("IP: error malloc"), NULL);
		if (pthread_mutex_init(&arr_philos[i]->meal_time_lock, 0) != 0)
			return (printf("IP: error mutex"), NULL);
		arr_philos[i]->table = table;
		arr_philos[i]->id = i;
		arr_philos[i]->times_ate = 0;
		assign_forks(arr_philos[i]);
		i++;
	}
	return (arr_philos);
}

static bool	init_g_mutexs(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->sim_stop_lock, 0) != 0)
		return (printf("IMG: error mutex"), free_table(table), false);
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
		return (printf("IMG: error mutex"), free_table(table), false);
	return (true);
}


t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (printf("IT: error malloc"), NULL);
	table->amount_philos = nbs_atoi(av[1]);
	table->t_t_die =  nbs_atoi(av[2]);
	table->t_t_eat =  nbs_atoi(av[3]);
	table->t_t_sleep =  nbs_atoi(av[4]);
	table->min_amount_meals = -1;
	if (ac == 6)
		table->min_amount_meals = nbs_atoi(5);
	table->philos = init_philos(table);
	if (!table->philos)
		return (NULL);
	if (!init_g_mutexs(table))
		return (NULL);
	table->sim_should_stop = false;
	return (table);
}
