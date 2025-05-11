/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 00:22:22 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/09 00:17:22 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**@brief wait for all threads to finish
 * @param *data Pointer to the data structure
 * @return returns void
*/
void	wait_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_join(data->philos[i].thread_id, NULL);
	pthread_join(data->death_monitor, NULL);
}

/**@brief Wait for all threads to be ready
 * @param *philo Pointer to the philo structure
 * @return returns void
*/
void	wait_all_threads(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->all_threads_ready)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		usleep(100);
	}
}

/**@brief Sleeps for a given time
 * @param *data Pointer to the data structure
 * @param sleep_time Time to sleep in microseconds
 * @return returns void
*/
void	ft_usleep(t_data *data, long sleep_time)
{
	long	wake_up;

	wake_up = get_current_time() + sleep_time / 1000;
	while (get_current_time() < wake_up)
	{
		if (simulation_finished(data))
		{
			break ;
		}
		usleep(50);
	}
}
