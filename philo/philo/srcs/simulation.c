/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:44:05 by bozil             #+#    #+#             */
/*   Updated: 2025/05/19 13:55:23 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	data->start_time = current_time();
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philos[i].thread, NULL, philosopher_life,
			&data->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_philosophers, data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int	is_dead(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->dead_mutex);
	result = data->dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (result);
}

void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}

long	get_last_meal(t_philo *philo)
{
	long	result;

	pthread_mutex_lock(&philo->meal_mutex);
	result = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (result);
}
