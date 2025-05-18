/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:51:31 by bozil             #+#    #+#             */
/*   Updated: 2025/05/17 23:44:22 by bozil            ###   ########.fr       */
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
