/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:38:28 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 16:05:26 by urlooved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// Will init amount of forks mutexes. (amount philos == amount forks)
// return array of forks or NULL. 
static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->amount_phis);
	if (!forks)
		return (printf("IF: error malloc"), NULL);
	i = 0;
	while (i < table->amount_phis)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (printf("IF: error mutexing"), NULL);
		i++;
	}
	return (forks);
}
// Will fill the array philosopher and init their values (table, id, time_ate)

static t_phi	**init_phis(t_table *table)
{
	t_phi			**arr_philos;
	unsigned int	i;

	if (!table)
		return (printf("IP: no table"), NULL);
	arr_philos = malloc(sizeof(t_phi) * table->amount_phis);
	if (!arr_philos)
		return (printf("IP: error malloc"), NULL);
	i = 0;
	while (i < table->amount_phis)
	{
		arr_philos[i] = malloc(sizeof(t_phi));					// Will create 1 t_phi per loop
		if (!arr_philos[i])
			return (printf("IP: error malloc"), NULL);
		if (pthread_mutex_init(&arr_philos[i]->meal_time_lock, 0) != 0)
			return (printf("IP: error mutex"), NULL);
		arr_philos[i]->table = table;
		arr_philos[i]->id = i;
		arr_philos[i]->times_ate = 0;
		arr_philos[i]->last_meal_at = table->start_meeting_at;
		set_forks(arr_philos[i]);
		i++;
	}
	return (arr_philos);
}

// Will init global muetexes (mutexes in struct table)
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

// Will init table, g_mutexes, philos array
t_table	*init_table_philos(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (printf("IT: error malloc"), NULL);
	table->amount_phis = nbs_atoi(av[1]);
	table->t_t_die =  nbs_atoi(av[2]);
	table->t_t_eat =  nbs_atoi(av[3]);
	table->t_t_sleep =  nbs_atoi(av[4]);
	table->sim_should_stop = false;
	table->min_amount_meals = -1;													// set by default to "NULL"
	table->start_meeting_at = get_time_in_ms() + (table->amount_phis * 2 * 10);		// the +... is to add some extra time to sync the threads and avoid data races
	if (ac == 6)																	// if we have 6 we update it to the inputed number
		table->min_amount_meals = nbs_atoi(av[5]);
	table->philos = init_phisophers(table);
	if (!table->philos)
		return (NULL);
	if (!init_global_mutexes(table))
		return (NULL);
	table->sim_should_stop = false;
	return (table);
}
