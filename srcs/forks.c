/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 23:38:03 by bozil             #+#    #+#             */
/*   Updated: 2025/05/18 19:28:42 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int take_left_fork(t_philo *philo)
{
    if (is_dead(philo->data))
        return (0);
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork on his left");
    if (philo->right_fork == NULL)
    {
        smart_sleep(philo, philo->data->time_to_die * 2);
        pthread_mutex_unlock(philo->left_fork);
        return (0);
    }
    return (1);
}

int	take_right_fork(t_philo *philo)
{
	if (is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork on his right");
	return (1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
}