/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 00:21:31 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/09 00:17:18 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_data	t_data;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	long		philo_nbr;
	long		meals_eaten;
	long		die;
	long		eat;
	long		sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		all_threads_ready; //syncro philos
	bool		end_simulation; // a philo dies or all philos full
	t_fork		*forks; // array forks
	t_philo		*philos; // array philos
	t_mtx		data_mutex;
	t_mtx		write_mutex;
	pthread_t	meal_monitor;
	pthread_t	death_monitor;
}	t_data;

int		init_philos(t_data *data, char **av);
void	clean_mallocs(t_data *data);
int		data_init(t_data *data);
void	error_print(char *text);
int		dinner_start(t_data *data, int i);
bool	simulation_finished(t_data *data);
long	get_current_time(void);
void	begin_simulation(t_data *data);
void	log_message(t_philo *philo, char *message);
void	wait_all_threads(t_philo *philo);
void	*death_monitor(void *args);
void	cleanup(t_data *data);
void	one(t_data *data);
void	wait_threads(t_data *data);
void	ft_usleep(t_data *data, long sleep_time);

#endif