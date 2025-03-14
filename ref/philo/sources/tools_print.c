/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:20:23 by rita          #+#    #+#             */
/*   Updated: 2022/07/17 10:40:16 by rita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/* print_status:
*	Prints a philosopher's status in plain text as required by the project
*	subject:
*		timestamp_in_ms X status
*/
// static void	print_status(t_phi *philo, char *str)
// {
// 	printf("%ld %d %s\n", (now_at() - philo->table->start_meeting_at), philo->id + 1, str);
// }

/* print_statement:
*	Prints the status of a philosopher as long as the simulation is
*	still active. Locks the write mutex to avoid intertwined messages
*	from different threads.
*
*	If DEBUG_FORMATTING is set to 1 in philo.h, the status will
*	be formatted with colors and extra information to help with debugging.
*	Otherwise the output will be the regular format required by the project
*	subject.
*/
// void	print_statement(t_phi *philo, bool reaper_report, t_status status)
// {
// 	pthread_mutex_lock(&philo->table->write_lock);
// 	if (should_sim_end(philo->table) == true && reaper_report == false)
// 	{
// 		pthread_mutex_unlock(&philo->table->write_lock);
// 		return ;
// 	}
// 	// // if (DEBUG_FORMATTING == true)
// 	// // {
// 	// // 	print_statement_debug(philo, status);
// 	// // 	pthread_mutex_unlock(&philo->table->write_lock);
// 	// // 	return ;
// 	// // }
// 	if (status == DIED)
// 		print_status(philo, "died");
// 	else if (status == EATING)
// 		print_status(philo, "is eating");
// 	else if (status == SLEEPING)
// 		print_status(philo, "is sleeping");
// 	else if (status == THINKING)
// 		print_status(philo, "is thinking");
// 	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
// 		print_status(philo, "has taken a fork");
// 	pthread_mutex_unlock(&philo->table->write_lock);
// }


// // static void	print_status(t_phi *philo, char *str)
// // {
// // 	printf("%ld %d %s\n", (now_at() - philo->table->start_meeting_at), philo->id + 1, str);
// // }

void	print_statement(t_phi *philo, char *status)
{
	time_t	process_at;
	int		philo_id;

	pthread_mutex_lock(&philo->table->write_lock);
	if (should_sim_end(philo->table) == true)					// if end of the process we cut the acces to write in the terminal
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


//  '------------------'
//!    not necesary
//  ,------------------,


// // /* print_status_debug:
// // *	Prints the philosopher's status in an easier to read,
// // *	colorful format to help with debugging. For fork-taking
// // *	statuses, extra information is displayed to show which fork
// // *	the philosopher has taken.
// // */
// // static void	print_status_debug(t_phi *philo, char *color,
// // 								char *str, t_status status)					//! not necesary 
// // {
// // 	if (status == GOT_FORK_1)
// // 		printf("[%10ld]\t%s%03d\t%s\e[0m: fork [%d]\n",
// // 			now_at() - philo->table->start_meeting_at,
// // 			color, philo->id + 1, str, philo->fork[0]);
// // 	else if (status == GOT_FORK_2)
// // 		printf("[%10ld]\t%s%03d\t%s\e[0m: fork [%d]\n",
// // 			now_at() - philo->table->start_meeting_at,
// // 			color, philo->id + 1, str, philo->fork[1]);
// // 	else
// // 		printf("[%10ld]\t%s%03d\t%s\e[0m\n",
// // 			now_at() - philo->table->start_meeting_at,
// // 			color, philo->id + 1, str);
// // }

// // /* print_statement_debug:
// // *	Redirects the status writing for debug mode. For this option,
// // *	the DEBUG_FORMATTING option must be set to 1 in philo.h.
// // */
// // static void	print_statement_debug(t_phi *philo, t_status status)				//! not necesary 
// // {
// // 	if (status == DIED)
// // 		print_status_debug(philo, RED, "died", status);
// // 	else if (status == EATING)
// // 		print_status_debug(philo, GREEN, "is eating", status);
// // 	else if (status == SLEEPING)
// // 		print_status_debug(philo, CYAN, "is sleeping", status);
// // 	else if (status == THINKING)
// // 		print_status_debug(philo, CYAN, "is thinking", status);
// // 	else if (status == GOT_FORK_1)
// // 		print_status_debug(philo, PURPLE, "has taken a fork", status);
// // 	else if (status == GOT_FORK_2)
// // 		print_status_debug(philo, PURPLE, "has taken a fork", status);
// // }



/* write_outcome:
*	Prints the outcome of the simulation if a number of times to
*	eat was specified. Only used for debug purposes.
*/
void	write_outcome(t_table *table) 											//! not necesary 
{
	unsigned int	i;
	unsigned int	full_count;

	full_count = 0;
	i = 0;
	while (i < table->amount_philos)
	{
		if (table->philos[i]->times_ate >= (unsigned int)table->min_amount_meals)
			full_count++;
		i++;
	}
	pthread_mutex_lock(&table->write_lock);
	printf("%d/%d philosophers had at least %d meals.\n",
		full_count, table->amount_philos, table->min_amount_meals);
	pthread_mutex_unlock(&table->write_lock);
	return ;
}
