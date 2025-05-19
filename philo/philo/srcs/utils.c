/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:51:31 by bozil             #+#    #+#             */
/*   Updated: 2025/05/19 16:20:56 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_meals(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->meals_mutex);
	result = philo->meals;
	pthread_mutex_unlock(&philo->meals_mutex);
	return (result);
}

void	sleep_and_think(t_philo *philo)
{
	philo_sleep(philo);
	think(philo);
}

int	take_right_fork_first(t_philo *philo)
{
	if (is_dead(philo->data))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	if (philo->left_fork == NULL)
	{
		smart_sleep(philo, philo->data->time_to_die * 2);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

int	take_left_fork_after_right(t_philo *philo)
{
	if (is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	return (1);
}
