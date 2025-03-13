/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:27:50 by rita          #+#    #+#             */
/*   Updated: 2022/07/08 12:28:08 by rita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* free_table:
*	Frees all of the memory allocated by the program.
*	Returns a NULL pointer if there is nothing to free,
*	or when all memory has been freed.
*/
void	free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return ;
	if (table->fork_locks != NULL)
		free(table->fork_locks);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->amount_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
}

/* destroy_mutexts:
*	Destroys every mutex created by the program: fork locks, meal locks,
*	the write and simulation stopper lock.
*/
static void	free_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->amount_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}

void	free_all(t_table *table)
{
	free_mutexes(table);
	free_table(table);
}

/* msg:
*	Writes a message to the console. Returns the provided exit number.
*	Used for error management.
*/
//! Will not use these function
int	msg(char *str, char *detail, int exit_no) //! no use
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (exit_no);
}

/* error_failure:
*	Frees any allocated memory, prints an error message and
*	returns 0 to indicate failure.
*	Used for error management during initialization.
*/

//! We will not use these function
int	error_failure(char *str, char *details, t_table *table) //! no use
{
	if (table != NULL)
		free_table(table);
	return (msg(str, details, 0));
}

/* error_null:
*	Frees any allocated memory, prints an error message and returns a NULL pointer.
*	Used for error management during initialization.
*/

//! We will not use these function
void	*error_null(char *str, char *details, t_table *table) //! no use
{
	if (table != NULL)
		free_table(table);
	msg(str, details, EXIT_FAILURE);
	return (NULL);
}
