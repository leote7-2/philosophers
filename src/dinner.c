/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 00:21:56 by joaoleote         #+#    #+#             */
/*   Updated: 2025/07/17 14:34:43 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**@brief Function to simulate the eating of a philosopher
 * @param *philo Pointer to the philo structure
 * @return void
*/
static void	philo_eat(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&first_fork->fork);
	log_message(philo, "has taken the first fork");
	pthread_mutex_lock(&second_fork->fork);
	log_message(philo, "has taken the second fork");
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->meals_counter++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->data_mutex);
	log_message(philo, "is eating");
	ft_usleep(philo->data, philo->data->eat * 1000);
	pthread_mutex_unlock(&second_fork->fork);
	pthread_mutex_unlock(&first_fork->fork);
}

/**@brief Function to simulate the sleeping of a philosopher
 * @param *philo Pointer to the philo strcuture
 * @return void
*/
static void	philo_sleep(t_philo *philo)
{
	log_message(philo, "is sleeping");
	ft_usleep(philo->data, philo->data->sleep * 1000);
}

/**@brief Function to simulate the thinking of a philosopher
 * @param *philo Pointer to the philo structure
 * @return void
*/
static void	philo_think(t_philo *philo)
{
	long	time_since_meal;
	long	time_to_think;

	log_message(philo, "is thinking");
	if (philo->data->philo_nbr % 2 == 0)
		return ;
	time_since_meal = get_current_time() - philo->last_meal_time;
	time_to_think = (philo->data->die - time_since_meal / 2);
	if (time_to_think < 120)
		return ;
	if (time_to_think > 120)
		time_to_think = 120;
	ft_usleep(philo->data, time_to_think * 1000);
}

/**@brief Function to simulate the dinner of the philosophers
 * @param *data Pointer to the data structure
 * @return void
*/
static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data, philo->data->eat / 2 * 1000);
	while (!simulation_finished(philo->data))
	{
		philo_eat(philo);
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->nbr_limit_meals > 0 && \
			philo->meals_counter == philo->data->nbr_limit_meals)
		{
			philo->data->meals_eaten++;
			if (philo->data->meals_eaten == philo->data->philo_nbr)
				philo->data->end_simulation = true;
			pthread_mutex_unlock(&philo->data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

/**@brief Initializes the dinner simulation
 * @param *data Pointer to the data structure
 * @param i Index of the philosopher
 * @return 0 if success, 1 if error
*/
int	dinner_start(t_data *data, int i)
{
	if (data->nbr_limit_meals == 0)
		return (0);
	if (data->philo_nbr == 1)
	{
		one(data);
		return (0);
	}
	else
	{
		while (++i < data->philo_nbr)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL, \
				dinner_simulation, &data->philos[i]) != 0)
				return (1);
		}
		begin_simulation(data);
		if (pthread_create(&data->death_monitor, NULL, \
			death_monitor, data) != 0)
			return (1);
		wait_threads(data);
		if (data->meals_eaten == data->philo_nbr)
			printf("All philosophers have eaten %ld times\n", \
				data->nbr_limit_meals);
		return (0);
	}
}
