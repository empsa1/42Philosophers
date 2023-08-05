/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:33:33 by eportela          #+#    #+#             */
/*   Updated: 2023/08/05 20:26:55 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define MUTEX_ERROR "Mutex failed to init"
# define UNDEFINED 	-1
# define PICKL_FORK  "has taken a fork"
# define PICKR_FORK  "has taken a fork"
# define DROP_FORK  "has dropped a fork"
# define EAT        "is eating"
# define SLEEP      "is sleeping"
# define THINK      "is thinking"
# define DEAD       "died"
# define BUSY       11
# define AVAILABLE  12
# define ALLOC_ERROR "failed to alloc memory"
# define PARAM_ERROR "Parameters where invalid"
# define THREAD_ERROR "Thread failed to initialize"
# define SLEEP_ERROR    "Failed to hold sleep"
# define FAILED		-10

typedef struct s_data	t_data;

typedef enum s_type
{
	TRUE,
	FAILURE,
	FALSE,
	SUCCESS,
	FORKING,
	THINKING,
	EATING,
	SLEEPING,
	DIED,
	DONE
}		t_type;

typedef struct s_fork
{
	pthread_mutex_t				fid;
	int							status;
}								t_fork;

typedef struct s_philo
{
	t_data						*r_table;
	pthread_mutex_t				stat;
	pthread_mutex_t				alive;
	pthread_mutex_t				main1;
	pthread_mutex_t				main2;
	int							flagg;
	int							id;
	pthread_t					pid;
	t_type						status;
	long						last_meal;
	int							n_meals;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	long int					timer;
	t_fork						*left_fork;
	t_fork						*right_fork;
}								t_philo;

struct s_data
{
	t_philo						*philos;
	int							p_n;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							number_of_must_meals;
	pthread_mutex_t				end;
	pthread_mutex_t				lmeal;
	pthread_mutex_t				stillm;
	pthread_mutex_t				lock;
	int							flag;
	int							flag1;
	long						time_sec;
	long						time_usec;
	int							n_thread;
	t_fork						*forks;
};

void			mealy(t_philo *philo);
int				checkforall(t_data *r_table);
void			close_program(t_data *r_table);
int				init_philo_easy(t_data *r_table, int i);
void			single_handler(t_philo *philo);

//src/phlo.c
int				input_to_data(t_data *r_table, char **args, int argc);
int				alloc_philosophers(t_data *r_table);
int				ft_spy(t_data *r_table);

//src/threads.c
int				init_philosophers(t_data *r_table, int i);
void			p_handler(t_philo *philo);
void			initpar_phil(t_data *r_table, int i);

//utils/aux_f.c
int				ft_positiveatoi(char *str);

//src/engine.c
int				is_alive(t_philo *philo);
int				still_has_meals(t_data *r_table);
void			start_thinking(t_philo *philo);
int				eating_1p(t_philo *philo);

//utils/system.c
unsigned long	get_time(void);
void			ft_sleep(int num);
long			ft_get_time(t_data *r_table);
void			ft_init_time(t_data *r_table);

//src/actions.c
void			start_eating(t_philo *philo);
void			pickl_forks(t_philo *philo);
void			pickr_forks(t_philo *philo);
void			drop_forks(t_philo *philo);
void			start_sleeping(t_philo *philo);

//utils/errors.c
void			message_handler(char *error_msg, int type, t_philo *philo);
int				is_validinput(char **args);
int				is_validint(long long n);
int				error_handler(char *str);

//utils/cleaners.c
void			clear_data(t_data *r_table);

#endif