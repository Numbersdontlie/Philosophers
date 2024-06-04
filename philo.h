/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:25:27 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/05 01:18:50 by luifer           ###   ########.fr       */
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

# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define RESET	"\033[0m"
# define ERROR -1
# define SUCCESS 0
# define MAX_PHILOS 200
# define TRUE 10
# define FALSE 20

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
	int				done_eating;
	long			time_last_eat;
	pthread_t		thread_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	struct s_data	*data;
	pthread_mutex_t	philo_status;
}	t_philo;

//Structure to represent the data of the simulation, it includes:
//number of philosophers, time to die, time to eat, time to sleep,
//number of times each philosopher must eat, the forks and the philosophers
typedef struct s_data
{
	int				num_philos;
	int				num_times_to_eat;
	int				all_done_eating;
	int				all_philos_ready;
	int				ready_to_begin;
	int				end_simulation;
	int				counter;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	long			start_time;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	start_mtx;
	pthread_mutex_t	finished_mtx;
	pthread_mutex_t	all_ready_mtx;
	pthread_mutex_t	simulation_done_mtx;
}	t_data;

int		ft_return_error(char *str);
int		ft_clean_exit(t_data *table, char *str);
//void	ft_free_memory(t_data *table);
void	ft_init_philos(t_data *table);
void	ft_initialize_mutex(pthread_mutex_t *mutex, t_data *table);
void	ft_init_forks(t_data *table);
void	ft_assign_forks(t_philo *philo, t_fork *forks, int num_philos);
long	ft_get_time(void);
void	ft_switch_mutex(pthread_mutex_t *mutex, int *value, int status);
int		ft_check_mutex(pthread_mutex_t *mutex, int *value);
int		ft_check_end(t_data *table);
void	ft_get_last_eat(t_philo *philo);
int		ft_check_die(t_philo *philo);
void	*ft_supervise(void *ptr);
int		ft_atol(char *nptr);
int		ft_check_input(int argc, char **argv);
int		ft_parse_input(t_data *table, char **argv);
void	ft_put_msg(t_philo *philo, char *str);
int		ft_sleep(size_t time_milliseconds);
int		ft_initialize_data(t_data *table, int argc, char **argv);
void	ft_philo_eat(t_philo *philo);
void	ft_philo_thinking(t_philo *philo);
//void	ft_take_fork(t_philo *philo);
void	*ft_single_philo(void *ptr);
void	ft_put_meals(t_data *table);
int		ft_start_simulation(t_data *table);
void	ft_destroy_mutex(t_data *table);
void	*ft_run_simulation(void *ptr);
int		ft_coordinate_start(t_data *table);

#endif