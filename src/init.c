/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 00:22:04 by joaoleote         #+#    #+#             */
/*   Updated: 2025/07/17 14:36:17 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**@brief Prints an error message and returns -1
 * @param void
 * @return Always returns -1
*/
long	exit_msg(void)
{
	printf("[ERROR invalid number]\n");
	return (-1);
}

/**@brief Verifies if the string is a number
 * @param *str Original string to check
 * @param *i Pointer to the index of the string
 * @param num Number to return
 * @return void
*/
long	check_spaces(char *str, int *i, int num)
{
	while (str[*i])
	{
		if (str[*i] != ' ')
			return (exit_msg());
		(*i)++;
	}
	return (num);
}

/**@brief Converts a string to a long interger
 * @param *str String to convert
 * @return Value of the number
*/
static long	ft_atol(char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = num * 10 + str[i] - '0';
			if (num > 2147483647)
				return (exit_msg());
		}
		else if (str[i] == ' ')
		{
			return (check_spaces(str, &i, num));
		}
		else
			return (exit_msg());
		i++;
	}
	return (num);
}

/**@brief Initializes the philosophers and their forks
 * @param *data Pointer to the data structure
 * @param **av Array of strings
 * @return Returns 0 if success, 1 in case of error
*/
int	init_philos(t_data *data, char **av)
{
	long	i;

	data->philo_nbr = ft_atol(av[1]);
	data->die = ft_atol(av[2]);
	data->eat = ft_atol(av[3]);
	data->sleep = ft_atol(av[4]);
	if (data->philo_nbr == -1 || data->die == -1 \
		|| data->eat == -1 || data->sleep == -1)
		return (1);
	if (data->die < 60 || data->eat < 60 \
		|| data->sleep < 60 || data->philo_nbr < 1)
	{
		error_print("[ERROR Use bigger time stamps]");
		return (1);
	}
	if (av[5])
	{
		i = ft_atol(av[5]);
		data->nbr_limit_meals = i;
		if (i == -1)
			return (1);
	}
	else
		data->nbr_limit_meals = -1;
	return (0);
}
