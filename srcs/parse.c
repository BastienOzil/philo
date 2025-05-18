/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 23:40:50 by bozil             #+#    #+#             */
/*   Updated: 2025/05/17 23:41:17 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_positive_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: invalid arguments, use 4 or 5 arguments only");
		printf(" with positive numbers\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_positive_number(argv[i]))
			return (printf("Error: invalid number\n"), 0);
		i++;
	}
	return (1);
}

int	parse_arguments(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (printf("Error: invalid values\n"), 0);
	return (1);
}

void	init_data_mutexes(t_data *data)
{
	data->dead = 0;
	data->start_time = current_time();
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
}