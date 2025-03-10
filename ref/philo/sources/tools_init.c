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

/* assign_forks:
*	Assigns two fork ids to each philosopher. Even-numbered philosophers
*	get their fork order switched. This is because the order in which
*	philosophers take their forks matters.
*
*	For example with 3 philos:
*		Philo #1 (id: 0) will want fork 0 and fork 1
*		Philo #2 (id: 1) will want fork 1 and fork 2
*		Philo #3 (id: 2) will want fork 2 and fork 0
*	If philo #1 takes fork 0, philo #2 takes fork 1 and philo #3 takes fork 2,
*	there is a deadlock. Each will be waiting for their second fork which is
*	in use by another philo.
*
*	Making even id philos "left-handed" helps:
*		Philo #1 (id: 0) takes fork 1 and then fork 0
*		Philo #2 (id: 1) takes fork 1 and then fork 2
*		Philo #3 (id: 2) takes fork 0 and then fork 2
*	Now, philo #1 takes fork 1, philo #3 takes fork 0 and philo #2 waits patiently.
*	Fork 2 is free for philo #3 to take, so he eats. When he is done philo #1 can
*	take fork 0 and eat. When he is done, philo #2 can finally get fork 1 and eat.
*/

// TODO in setters
static void	assign_forks(t_philo *philo) // TODO
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->amount_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->amount_philos;
		philo->fork[1] = philo->id;
	}
}

/* init_philosophers:
*	Allocates memory for each philosopher and initializes their values.
*	Returns a pointer to the array of philosophers or NULL if
*	initialization failed.
*/
static t_philo	**init_philosophers(t_table *table)
{
	t_philo			**arr_philo;
	unsigned int	i;

	if (!table)
		return (printf("IP: no table"), NULL);
	arr_philo = malloc(sizeof(t_philo) * table->amount_philos);
	if (!arr_philo)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < table->amount_philos)
	{
		arr_philo[i] = malloc(sizeof(t_philo) * 1);
		if (!arr_philo[i])
			return (error_null(STR_ERR_MALLOC, NULL, 0));
		if (pthread_mutex_init(&arr_philo[i]->meal_time_lock, 0) != 0)
			return (error_null(STR_ERR_MUTEX, NULL, 0));
		arr_philo[i]->table = table;
		arr_philo[i]->id = i;
		arr_philo[i]->times_ate = 0;
		assign_forks(arr_philo[i]);
		i++;
	}
	return (arr_philo);
}

/* init_global_mutexes:
*	Initializes mutex locks for forks, writing and the stop simulation
*	flag.
*	Returns true if the initalizations were successful, false if
*	initilization failed.
*/
static bool	init_global_mutexes(t_table *table)
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

/* init_table:
*	Initializes the "dining table", the data structure containing
*	all of the program's parameters.
*	Returns a pointer to the allocated table structure, or NULL if
*	an error occured during initialization.
*/
t_table	*init_table(int ac, char **av, int i)
{
	t_table	*table;

	table = malloc(sizeof(t_table));					// we need only 1 table (always)
	if (!table)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	table->amount_philos = nbs_atoi(av[i++]);
	table->time_to_die = nbs_atoi(av[i++]);
	table->time_to_eat = nbs_atoi(av[i++]);
	table->time_to_sleep = nbs_atoi(av[i++]);
	table->min_amount_meals = -1;						// set by default to "NULL"
	if (ac == 6)										// if we have 6 we update it to the inputed number
		table->min_amount_meals = nbs_atoi(av[i]);
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (NULL);
	if (!init_global_mutexes(table))
		return (NULL);
	table->sim_should_stop = false;
	return (table);
}
