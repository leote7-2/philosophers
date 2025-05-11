/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 00:22:18 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/08 23:43:31 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**@brief Prints an error message
 * @param *text Pointer to the text to print
 * @return returns void
*/
void	error_print(char *text)
{
	printf("%s\n", text);
}

/**@brief Checks if the simulation is finished
 * @param *data Pointer to the data structure
 * @return returns True if the simulation is finished, false otherwise
*/
bool	simulation_finished(t_data *data)
{
	bool	ret;

	pthread_mutex_lock(&data->data_mutex);
	ret = data->end_simulation;
	pthread_mutex_unlock(&data->data_mutex);
	return (ret);
}

/**@brief Gets the current time in milliseconds
 * @param void void
 * @return returns Current time in milliseconds
*/
long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**@brief Initializes the simulation
 * @param *data Pointer to the data structure
 * @return returns void
*/
void	begin_simulation(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->data_mutex);
	data->start_simulation = get_current_time();
	while (++i < data->philo_nbr)
		data->philos[i].last_meal_time = data->start_simulation;
	data->all_threads_ready = true;
	pthread_mutex_unlock(&data->data_mutex);
}

/**@brief Registers a message with a timestamp
 * @param *philo Pointer to the philo structure
 * @param *message Pointer to the message to print
 * @return returns void
*/
void	log_message(t_philo *philo, char *message)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->data_mutex);
	if (!philo->data->end_simulation)
	{
		timestamp = get_current_time() - philo->data->start_simulation;
		printf("[%ld] %d %s\n", timestamp, philo->id, message);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
}
