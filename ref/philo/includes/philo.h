/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rita <rita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:46:01 by rita          #+#    #+#             */
/*   Updated: 2022/08/06 15:21:48 by rita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

/******************************************************************************
*                                     Macros                                  *
******************************************************************************/

# define MAX_PHILOS	250
# define STR_MAX_PHILOS "250"

# ifndef DEBUG_FORMATTING
#  define DEBUG_FORMATTING 0
# endif

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define STR_PROG_NAME	"philo:"
# define STR_USAGE	"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW	"%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"%s error: Could not create mutex.\n"

/******************************************************************************
*                                 Structures                                  *
******************************************************************************/

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t			start_meeting_at;
	unsigned int	amount_philos;
	pthread_t		t_stop_program;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				min_amount_meals;
	bool			sim_should_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}	t_table;

typedef struct s_philo
{
	unsigned int		id;
	pthread_t			thread_id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal_at;
	t_table				*table;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

//	parsing.c
bool			are_valid_input(int ac, char **av);
int				nbs_atoi(char *str);

//	init.c
t_table			*init_table(int ac, char **av);

//	routines.c
void			*philosopher(void *data);

// tools_setters.c
void	set_forks(t_philo *philo);
void	set_sim_should_stop_flag(t_table *table, bool state);

// tools_observers
bool	has_simulation_stopped(t_table *table);


//	time.c
time_t			get_time_in_ms(void);
void			set_philo_sleep(t_table *table, time_t sleep_time);
void			sim_start_delay(time_t start_meeting_at);

//	output.c
void			write_status(t_philo *philo, bool reaper, t_status status);
void			write_outcome(t_table *table);
void			*error_null(char *str, char *details, t_table *table);
int				msg(char *str, char *detail, int exit_no);

//	t_stop_program.c
void			*t_stop_program(void *data);
bool			has_simulation_stopped(t_table *table);

//	exit.c
int				error_failure(char *str, char *details, t_table *table);
void			free_table(t_table *table);
void			free_mutexes(t_table *table);

#endif