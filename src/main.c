/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 00:22:09 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/08 16:47:40 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**@brief Simulates the behavior of a single philosopher
 * @param *data Pointer to the data structure
 * @return void
*/
void	one(t_data *data)
{
	data->start_simulation = get_current_time();
	log_message(&data->philos[0], "has taken a fork");
	usleep(data->die * 1000);
	printf("[%ld] %d died\n", get_current_time() - \
		data->start_simulation, data->philos[0].id);
	data->end_simulation = true;
}

/**@brief Erases the mutexes and frees the memory
 * @param *data Pointer to the data structure
 * @return void
*/
void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->forks[i].fork);
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

/**@brief Frees the allocated memory
 * @param *data Pointer to the data structure
 * @return void
*/
void	clean_mallocs(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

/**@brief Prints an error message and cleans up the memory
 * @param *data Pointer to the data structure
 * @param *str String with an error message
 * @return returns 1 if error, 0 if success
*/
int	finish(t_data *data, const char *str)
{
	printf("%s\n", str);
	cleanup(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = -1;
	if (ac == 5 || ac == 6)
	{
		if (init_philos(&data, av) == 1)
			return (1);
		if (data_init(&data) != 0)
			return (finish(&data, "[ERROR Failed to initialize data]\n"));
		if (dinner_start(&data, i) == 1)
			return (finish(&data, "[ERROR thread creation failed]\n"));
		cleanup(&data);
	}
	else
	{
		printf("[ERROR wrong input]\n");
		return (1);
	}
	return (0);
}
