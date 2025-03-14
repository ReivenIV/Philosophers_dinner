/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:35:04 by rita          #+#    #+#             */
/*   Updated: 2022/11/15 15:49:54 by rita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* intit_forks:
*	Allocates memory and initializes fork mutexes.
*	Returns a pointer to the fork mutex array, or NULL if an error occured. 
*/
static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->amount_philos);
	if (!forks)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < table->amount_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_null(STR_ERR_MUTEX, NULL, 0));
		i++;
	}
	return (forks);
}



/* init_phisophers:
*	Allocates memory for each philosopher and initializes their values.
*	Returns a pointer to the array of philosophers or NULL if
*	initialization failed.
*/
static t_phi	**init_phis(t_table *table)
{
	t_phi			**arr_philos;
	unsigned int	i;

	if (!table)
		return (printf("IP: no table"), NULL);
	arr_philos = malloc(sizeof(t_phi) * table->amount_philos);
	if (!arr_philos)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < table->amount_philos)
	{
		arr_philos[i] = malloc(sizeof(t_phi) * 1);
		if (!arr_philos[i])
			return (error_null(STR_ERR_MALLOC, NULL, 0));
		if (pthread_mutex_init(&arr_philos[i]->meal_time_lock, 0) != 0)
			return (error_null(STR_ERR_MUTEX, NULL, 0));
		arr_philos[i]->table = table;
		arr_philos[i]->id = i;
		arr_philos[i]->times_ate = 0;
		arr_philos[i]->last_meal_at = table->start_meeting_at;
		set_forks(arr_philos[i]);
		i++;
	}
	return (arr_philos);
}

/* init_g_mutexes:
*	Initializes mutex locks for forks, writing and the stop simulation
*	flag.
*	Returns true if the initalizations were successful, false if
*	initilization failed.
*/
static bool	init_g_mutexes(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->sim_stop_lock, 0) != 0)
		return (printf("IGM: error while init"), free_table(table), false);
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
		return (printf("IGM: error while init"), free_table(table), false);
	return (true);
}

/* init_table_philos:
*	Initializes the "dining table", the data structure containing
*	all of the program's parameters.
*	Returns a pointer to the allocated table structure, or NULL if
*	an error occured during initialization.
*/
t_table	*init_table_philos(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));					// we need only 1 table (always)
	if (!table)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	table->amount_philos = nbs_atoi(av[1]);
	table->t_t_die = nbs_atoi(av[2]);
	table->t_t_eat = nbs_atoi(av[3]);
	table->t_t_sleep = nbs_atoi(av[4]);
	table->t_t_think = 0;
	table->sim_should_stop = false;
	table->min_amount_meals = -1;						// set by default to "NULL"
	table->start_meeting_at = get_current_time() + (table->amount_philos * 2 * 10);		// the +... is to add some extra time to sync the threads and avoid data races
	if (ac == 6)										// if we have 6 we update it to the inputed number
		table->min_amount_meals = nbs_atoi(av[5]);
	table->philos = init_phis(table);
	if (!table->philos)
		return (NULL);
	if (!init_g_mutexes(table))
		return (NULL);
	table->sim_should_stop = false;
	return (table);
}
