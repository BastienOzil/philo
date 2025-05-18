/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:06:48 by bozil             #+#    #+#             */
/*   Updated: 2025/05/17 23:39:16 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_data(&data, argc, argv))
		return (1);
	if (init_philos(&data))
		return (free_data(&data), 1);
	start_simulation(&data);
	cleanup(&data);
	return (0);
}
