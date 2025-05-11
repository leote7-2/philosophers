/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 00:22:13 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/08 23:35:04 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**@brief Checks if the simulation is finished
 * @param *philo Pointer to the philo structure
 * @return returns true if the philo died, false otherwise
*/
static bool	check_death(t_philo *philo)
{
	long	current_time;
	long	last_meal;
	bool	died;

	pthread_mutex_lock(&philo->data->data_mutex);
	last_meal = philo->last_meal_time;
	current_time = get_current_time();
	died = (current_time - last_meal >= philo->data->die);
	if (died && !philo->data->end_simulation)
	{
		printf("[%ld] %d died\n", current_time - \
			philo->data->start_simulation, philo->id);
		philo->data->end_simulation = true;
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (died);
}

/**@brief Thread function to monitor the death of philosophers
 * @param *args Pointer to the data structure
 * @return returns NULL
*/
void	*death_monitor(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (!simulation_finished(data))
	{
		i = -1;
		while (++i < data->philo_nbr)
		{
			if (simulation_finished(data))
				return (NULL);
			if (check_death(&data->philos[i]))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
