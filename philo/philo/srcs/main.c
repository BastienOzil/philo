/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:06:48 by bozil             #+#    #+#             */
/*   Updated: 2025/05/19 16:25:20 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		sleep_time;
	int		temp;

	if (ft_strcmp(argv[1], "1") == 0)
	{
		sleep_time = ft_atoi(argv[2]);
		temp = ft_atoi(argv[2]) * 1000;
		usleep(temp);
		printf("0 1 has taken a fork\n");
		printf("%d 1 has died\n", sleep_time);
		return (0);
	}
	if (!init_data(&data, argc, argv))
		return (1);
	if (init_philos(&data))
		return (free_data(&data), 1);
	start_simulation(&data);
	cleanup(&data);
	return (0);
}
