/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:02:53 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 17:21:46 by rita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>	// to create threads and mutex
# include <limits.h>	// INT_MIN/MAX
# include <unistd.h>	// for usleep() & write
# include <stdio.h>		// malloc
# include <stdlib.h>
# include <sys/time.h>	// To get current time
# include <stdbool.h>	// because i love bools

//	---------------
//	::  Structs  ::
//	---------------
typedef struct s_philo	t_phi;
typedef struct s_table
{
	time_t				start_meeting_at;
	unsigned int		amount_philos;
	time_t				t_t_die;
	time_t				t_t_eat;
	time_t				t_t_sleep;
	time_t				t_t_think;
	int					min_amount_meals;
	pthread_t			t_handler_stop_program;
	bool				sim_should_stop;
	pthread_mutex_t		sim_stop_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		*fork_locks;
	t_phi				**philos;
}	t_table;

typedef struct s_philo
{
	unsigned int		id;
	pthread_t			thread_id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		phi_action_lock;
	time_t				last_meal_at;
	t_table				*table;
}	t_phi;

//	----------------
//	::  handlers  ::
//	----------------

bool	handler_parser(int ac, char **av);
bool	begin_process(t_table *table);
void	*t_handler_philo(void *data);
void	*t_handler_stop_program(void *data);
void	end_process(t_table *table);

//	-------------
//	::  Tools  ::
//	-------------

// tools_init
t_table	*init_table_philos(int ac, char **av);

// tools_time:
time_t	now_at(void);
void	sync_threads(time_t start_meeting_at);

// tools_print:
void	print_statement(t_phi *philo, char *status);

//  tools_philo_actions
void	eat_sleep_process(t_phi *philo);
void	think_process(t_table *t, t_phi *p, time_t lma);
void	start_think_even(t_phi *philo);
void	*wait_till_die(t_phi *philo);

// tools_setters
void	set_phi_to(char *activity, t_phi *philo);
void	set_forks(t_phi *philo);
void	update_sim_should_stop(t_table *table, bool state);

// tools_obersevers
bool	should_sim_end(t_table *table);
bool	is_philo_dead(t_phi *philo);
bool	are_all_conditions_reached(t_table *table);

// tools_strs
int		nbs_atoi(char *str);
bool	has_only_digits(char *str);

// tools_free
void	free_table(t_table *table);
void	free_all(t_table *table);

#endif