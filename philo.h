/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:25:27 by lperez-h          #+#    #+#             */
/*   Updated: 2024/05/06 23:08:56 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define RED	"\033[0;31m";
# define GREEN	"\033[0;32m";
# define YELLOW	"\033[0;33m";
# define RESET	"\033[0m";
# define ERROR -1
# define SUCCESS 0
# define MAX_PHILOS 200

//Structure to represent the fork with a mutex and an id
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

//Structure to represent Philosophers data, it includes:
//id of philo, number of times it has eaten, time of last eat, 
//if it has finished eating, the thread and a pointer to the data
typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				time_last_eat;
	int				done_eating;
	pthread_t		thread_id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_data	*data;
	pthread_mutex_t	is_done_eating;
	pthread_mutex_t	is_eating;
}	t_philo;

//Structure to represent the data of the simulation, it includes:
//number of philosophers, time to die, time to eat, time to sleep,
//number of times each philosopher must eat, the forks and the philosophers
typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	int				num_times_to_eat;
	long			start_time;
	int				end_simulation;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor;
}	t_data;

int		ft_return_error(char *str);
int		ft_atol(char *nptr);
int		ft_check_input(char **argv);
int		ft_parse_input(t_data *table, char **argv);

#endif