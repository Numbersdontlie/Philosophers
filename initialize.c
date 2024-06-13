/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:57:56 by luifer            #+#    #+#             */
/*   Updated: 2024/06/13 12:57:39 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atol(char *nptr);

//Function to convert a string to a long
static int	ft_atol(char *nptr)
{
	long	result;

	result = 0;
	while (((*nptr >= 9) && (*nptr <= 13)) || (*nptr == 32))
		nptr++;
	if (*nptr == 43)
		nptr++;
	while ((*nptr >= 48) && (*nptr <= 57))
	{
		result = ((result * 10) + (*nptr - 48));
		nptr++;
	}
	return (result);
}

//Function to parse the input received from the user
//It checks if the time to die, eat and sleep are at least 60ms
//It populates the data structure with the input
//It also initializes the mutexes of the table
int	ft_parse_input(t_data *table, int argc, char **argv)
{
	table->num_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->num_times_to_eat = ft_atol(argv[5]);
	else
		table->num_times_to_eat = -1;
	if (table->time_to_die < 60 || table->time_to_eat < 60
			|| table->time_to_sleep < 60)
		return (ft_return_error("ERROR: time in ms, min 60"));
	return (SUCCESS);
}

//Function to allocate memory for the philos, forks and mutexes
int	ft_allocate_memory(t_data *table)
{
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		ft_clean_exit(table, RED"Error: Malloc failed philo\n"RESET);
	table->forks = malloc(sizeof(t_fork) * table->num_philos);
	if (!table->forks)
		ft_clean_exit(table, RED"Error: Malloc failed fork\n"RESET);
	return (SUCCESS);
}

//Function to initialize the philosophers in the table
//It assigns to each philosopher: the table, the id, a flag to 
//know when is done eating, the numeber of times it has eaten, 
//the time of last eat, the mutex to know when is done eating,
//the mutex to know when is eating, and assign forks.
void	ft_init_philos(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].data = table;
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].time_last_eat = ft_get_time();
		table->philos[i].done_eating = NO;
		pthread_mutex_init(&table->philos[i].philo_done_mtx, NULL);
		pthread_mutex_init(&table->philos[i].philo_last_mtx, NULL);
		ft_assign_forks(&table->philos[i], table->forks);
		i++;
	}
}

//Function to assign the forks to the philosophers
//odd philos start with left fork, even philos start with right fork
void	ft_assign_forks(t_philo *philo, t_fork *fork)
{
	if (philo->id % 2 != 0)
	{
		philo->first_fork = &fork[philo->id % philo->data->num_philos];
		philo->second_fork = &fork[philo->id - 1];
	}
	else
	{
		philo->first_fork = &fork[philo->id - 1];
		philo->second_fork = &fork[philo->id % philo->data->num_philos];
	}
}

//Function to initialize the values of the table
//It allocates memory for the philos and forks and 
//Initialize the philos and forks and assign the forks to the philos
int	ft_initialize_data(t_data *table)
{
	int	i;

	i = 0;
	if (ft_allocate_memory(table) == ERROR)
		return (ERROR);
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].id = i;
		i++;
	}
	table->time_to_think = table->time_to_die - table->time_to_eat
		- table->time_to_sleep;
	table->end_simulation = NO;
	table->all_philos_ready = NO;
	ft_init_mtx_table(&table->all_ready_mtx, table);
	ft_init_mtx_table(&table->finished_mtx, table);
	ft_init_mtx_table(&table->print_mtx, table);
	ft_init_philos(table);
	table->start_time = ft_get_time();
	return (SUCCESS);
}
