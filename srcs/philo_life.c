/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 23:42:39 by bozil             #+#    #+#             */
/*   Updated: 2025/05/18 19:24:48 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo->data))
	{
		eat(philo);
		if (philo->data->number_of_times_each_philosopher_must_eat > 0
			&& get_meals(philo) >= philo->data->number_of_times_each_philosopher_must_eat)
			break ;
		if (is_dead(philo->data))
			break ;
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

int	check_all_ate_enough(t_data *data)
{
	int	i;
	int	all_ate_enough;

	if (data->number_of_times_each_philosopher_must_eat <= 0)
		return (0);
	all_ate_enough = 1;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (get_meals(&data->philos[i]) < data->number_of_times_each_philosopher_must_eat)
		{
			all_ate_enough = 0;
			break ;
		}
		i++;
	}
	return (all_ate_enough);
}

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (current_time() - get_last_meal(&data->philos[i]) > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			if (!is_dead(data))
			{
				printf("%ld %d died\n",
					current_time() - data->start_time, data->philos[i].id);
				set_dead(data);
			}
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_philosophers(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!is_dead(data))
	{
		if (check_death(data))
			return (NULL);
		if (check_all_ate_enough(data))
		{
			set_dead(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}


void smart_sleep(t_philo *philo, long time)
{
    long start;

    start = current_time();
    while ((current_time() - start) < time)
    {
        if (is_dead(philo->data))
            return;
        usleep(100);
    }
}
