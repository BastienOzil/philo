/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:39:41 by bozil             #+#    #+#             */
/*   Updated: 2025/05/17 23:42:01 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	if (!validate_arguments(argc, argv))
		return (0);
	if (!parse_arguments(data, argc, argv))
		return (0);
	init_data_mutexes(data);
	if (init_forks(data))
		return (0);
	data->philos = NULL;
	return (1);
}

void	init_single_philo(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].last_meal = current_time();
	pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
	data->philos[i].meals = 0;
	pthread_mutex_init(&data->philos[i].meals_mutex, NULL);
	data->philos[i].data = data;
	data->philos[i].left_fork = &data->forks[i];
	if (data->number_of_philosophers > 1)
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->number_of_philosophers];
	else
		data->philos[i].right_fork = NULL;
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		init_single_philo(data, i);
		i++;
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		pthread_mutex_destroy(&data->philos[i].meals_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	free(data->forks);
	if (data->philos)
		free(data->philos);
}
