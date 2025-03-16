/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urlooved <urlooved@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:02:53 by urlooved          #+#    #+#             */
/*   Updated: 2025/03/16 17:19:06 by urlooved             ###   ########.fr       */
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
typedef struct	s_philo	t_phi;

typedef struct s_table
{
	time_t				start_meeting_at;				// meeting created_at
	unsigned int		amount_philos;
	time_t				t_t_die;						// amount ms of time to die present in AV
	time_t				t_t_eat;						// amount ms of time to eat present in AV
	time_t				t_t_sleep;						// amount ms of time to sleep present in AV
	time_t				t_t_think;						// amount ms of time to sleep need to calculate. (check think_process)
	int					min_amount_meals;				// min amount of meals that every philo must eat before end of process
	pthread_t			t_handler_stop_program;			// a thread that will be checking is we need to stop the program
	bool				sim_should_stop;				// t_handler_stop_program will be checking these var constantly.
	pthread_mutex_t		sim_stop_lock;					// t_handler_stop_program will constantly check these var.. when TRUE == end of the process
	pthread_mutex_t		write_lock;						// mutex to manage wich thread can write or not.
	pthread_mutex_t		*fork_locks;					// Array of mutexes Forks we will have/use during the process 
	t_phi				**philos;						// array of philos
} t_table; 

typedef struct s_philo
{
	unsigned int		id;							// Id of each philosopher
	pthread_t			thread_id;					// each philo/thread
	unsigned int		times_ate;					// amount of meals per philo
	unsigned int		fork[2];					// max 2F per Philo, these will be related to the index of philo_id. But we will use then to locate the mutex fork id. (fork_locks)
	pthread_mutex_t		phi_action_lock;			// mutex to handle interactions of each philosopher(thread)
	time_t				last_meal_at;				// timestamp that record last meal eaten (usefull to know if any philo already died)
	t_table				*table;
} t_phi;

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
//	::  handlers  ::
//	----------------

bool	handler_parser(int ac, char **av);		// Check if all inputs are correct.
bool	begin_process(t_table *table);			// Will create all threads/mutexes and call t_handler_philo & t_handler_stop_program.
void	*t_handler_philo(void *data);			// Will handle the global process, eat, sleep, think & die.
void	*t_handler_stop_program(void *data);	// WIll constantly check if the process reached all conditions to end.
void	end_process(t_table *table);			// at the end, Will free everything.


//	-------------
//	::  Tools  ::
//	-------------

// tools_init
t_table	*init_table_philos(int ac, char **av);

// tools_time: 
time_t	now_at(void);
void	sync_threads(time_t start_meeting_at);

// tools_print:  
void	print_statement(t_phi *philo, char *status);		// We will print everything with these function. Is like a "print handler";

//  tools_philo_actions
void	eat_sleep_process(t_phi *philo);					// Main action only eat _ sleep
void	think_process(t_table *t, t_phi *p, time_t lma);	// calculate t_t_think. REMINDER ODD vs EVEN not the same
void 	start_think_even(t_phi *philo);						// only at the begining only for EVEN philos.
void	*wait_till_die(t_phi *philo);						// Only for 1 philo.


// tools_setters
void	set_phi_to(char *activity, t_phi *philo);			// Will put philos to eat, sleep, think, die
void	set_forks(t_phi *philo);							// Will assign forks to every philosopher
void	update_sim_should_stop(t_table *table, bool state);	// Will update the var : sim_should_stop checked by (handler)begin_process -> (handler)t_handler_stop_program

// tools_obersevers
bool	should_sim_end(t_table *table);
bool	is_philo_dead(t_phi *philo);						// WIll check if all philos are alive. If no, handle and call to stop the process.
bool	are_all_conditions_reached(t_table *table);

// tools_strs
int		nbs_atoi(char *str);
bool	has_only_digits(char *str);

// tools_free
void	free_table(t_table *table);							// only free table.
void	free_all(t_table *table);							// Free all global and single mutexes + free_table.

#endif