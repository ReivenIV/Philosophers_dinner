/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:02:53 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/13 15:33:07 by urlooved         ###   ########.fr       */
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


//	------------------
//	::  parameters  ::
//	------------------

//	---------------
//	::  Structs  ::
//	---------------
typedef struct	s_philo	t_philo;

typedef struct s_table
{
	time_t				start_meeting_at;				// meeting created_at
	unsigned int		amount_philos;
	time_t				t_t_die;						// amount ms of time to die
	time_t				t_t_eat;						// amount ms of time to eat
	time_t				t_t_sleep;						// amount ms of time to sleep
	unsigned int		min_amount_meals;				// min amount of meals that every philo must eat before end of process
	pthread_t			t_stop_program;					// a thread that will be checking is we need to stop the program
	bool				sim_should_stop;				// BOOL true/false 
	pthread_mutex_t		sim_stop_lock;					// TODO check if necesary
	pthread_mutex_t		write_lock;						// mutex to manage wich thread can write or not.
	pthread_mutex_t		*fork_locks;					// mutex that manage the fork handling to every philo
	t_philo				**philos;						// array of philos
} t_table; 

typedef struct s_philo
{
	unsigned int		id;							// Id of each philosopher
	pthread_t			thread_id;					// thread_id of each philo
	unsigned int		times_ate;					// amount of meals per philo
	unsigned int		fork[2];					// max amount of forks per philo
	pthread_mutex_t		meal_time_lock;				//? time to eat ?
	time_t				last_meal_at;				// timestamp that record last meal eaten (usefull to know if any philo already died)
	t_table				*table;
} t_philo;

//	-------------
//	::  Enums  ::
//	-------------
// // typedef enum e_status
// // {
// // 	DIED = 0,
// // 	EATING = 1,
// // 	SLEEPING = 2,
// // 	THINKING = 3,
// // 	GOT_FORK_1 = 4,
// // 	GOT_FORK_2 = 5
// // }	t_status;

//	----------------
//	::  Handlers  ::
//	----------------

//	-------------
//	::  Tools  ::
//	-------------

// parser
bool	are_inputs_valid(int ac, char **av);

// tools_init
t_table	*init_table_philos(int ac, char **av);

// tools_time: 
time_t	get_current_time(void);

// tools_print:  
void	print_statement(t_philo *philo, char *status);

// tools_setters
void	set_philo_to(char *activity, t_table *table, time_t activity_time, t_philo *philo);
void	set_forks(t_philo *philo);
void	update_sim_should_stop(t_table *table, bool state);

// tools_obersevers
bool	should_sim_end(t_table *table);
bool	is_philo_dead(t_philo *philo);
bool	are_all_conditions_reached(t_table *table);
void	*t_stop_program(void *data);

// tools_strs
int	ft_strlen(char *str);
int	nbs_atoi(char *str);

// tools_free
void	free_table(t_table *table);
void	free_mutexes(t_table *table);

//	------------
//	::  Free  ::
//	------------







#endif