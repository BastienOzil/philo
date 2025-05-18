/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:57:16 by bozil             #+#    #+#             */
/*   Updated: 2025/05/18 19:28:10 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long			start_time;
	int				dead;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

/* actions.c */
void	print_status(t_philo *philo, char *status);
void	update_meal_info(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

/* forks.c */
int		init_forks(t_data *data);
int		take_left_fork(t_philo *philo);
int		take_right_fork(t_philo *philo);
void	release_forks(t_philo *philo);
void	free_data(t_data *data);

/* parse.c */
long	current_time(void);
int		is_positive_number(const char *str);
int		validate_arguments(int argc, char **argv);
int		parse_arguments(t_data *data, int argc, char **argv);
void	init_data_mutexes(t_data *data);

/* init.c */
int		init_data(t_data *data, int argc, char **argv);
void	init_single_philo(t_data *data, int i);
int		init_philos(t_data *data);
void	cleanup(t_data *data);

/* philo_life.c */
void	*philosopher_life(void *arg);
int		check_all_ate_enough(t_data *data);
int		check_death(t_data *data);
void	*monitor_philosophers(void *arg);
void	smart_sleep(t_philo *philo, long time);

/* simulation.c */
void	start_simulation(t_data *data);
int		is_dead(t_data *data);
void	set_dead(t_data *data);
void	update_last_meal(t_philo *philo);
long	get_last_meal(t_philo *philo);

/* utils.c */
int		get_meals(t_philo *philo);
void	sleep_and_think(t_philo *philo);

#endif