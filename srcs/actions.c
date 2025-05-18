/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:48:03 by bozil             #+#    #+#             */
/*   Updated: 2025/05/18 19:25:44 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_dead(philo->data))
		printf("%ld %d %s\n", current_time() - philo->data->start_time,
			philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	update_meal_info(t_philo *philo)
{
	update_last_meal(philo);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_mutex);
}

void eat(t_philo *philo)
{
    if (is_dead(philo->data))
        return;
    if (!take_left_fork(philo))
        return;
    if (!take_right_fork(philo))
        return;
    print_status(philo, "is eating");
    update_meal_info(philo);
    smart_sleep(philo, philo->data->time_to_eat);
    release_forks(philo);
}

void philo_sleep(t_philo *philo)
{
    if (is_dead(philo->data))
        return;
    print_status(philo, "is sleeping");
    smart_sleep(philo, philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (is_dead(philo->data))
		return ;
	print_status(philo, "is thinking");
}
