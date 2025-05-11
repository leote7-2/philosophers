/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 00:21:47 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/08 14:37:45 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**@brief Set the right and left forks of the philosophers
 * @param *philo Pointer to the philosopher
 * @param *data Pointer to the data structure
 * @param i Index of the philosopher
 * @return void
*/
static void	set_forks(t_philo *philo, t_data *data, int i)
{
	if (data->philo_nbr == 1)
	{
		philo->left_fork = &data->forks[0];
		philo->right_fork = &data->forks[0];
	}
	else
	{
		philo->left_fork = &data->forks[(i + 1) % data->philo_nbr];
		philo->right_fork = &data->forks[i];
	}
}

/**@brief Initializes the philosophers and their forks
 * @param *data Pointer to the data structure
 * @return void
*/
static void	philo_fill_data(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->philos;
	i = -1;
	while (++i < data->philo_nbr)
	{
		philo[i].id = i + 1;
		philo[i].meals_counter = 0;
		philo[i].full = false;
		philo[i].data = data;
		set_forks(&philo[i], data, i);
	}
}

/**@brief Shows an error message and returns 1
 * @param *str String with an error message
 * @return Always 1 indicating an error
*/
int	error_message(const char *str)
{
	printf("%s\n", str);
	return (1);
}

/**@brief Initializes the data structure, including philosophers forks and mutexes
 * @param *data Pointer to the data structure
 * @return 0 if success, 1 if error
*/
int	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->end_simulation = false;
	data->meals_eaten = 0;
	data->all_threads_ready = false;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->philos || !data->forks)
	{
		clean_mallocs(data);
		return (error_message("[ERROR Memory allocation failed]\n"));
	}
	while (++i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
			return (error_message("[ERROR Mutex failed]\n"));
		data->forks[i].fork_id = i;
	}
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (error_message("[ERROR Mutex failed]\n"));
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (error_message("[ERROR Mutex failed]\n"));
	philo_fill_data(data);
	return (0);
}
