/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:57:56 by luifer            #+#    #+#             */
/*   Updated: 2024/05/22 21:13:08 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to allocate memory for the philos, forks and mutexes
void	ft_allocate_memory(t_data *table)
{
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		ft_return_error(RED"Error: Malloc failed philo\n"RESET);
	table->forks = malloc(sizeof(t_fork) * table->num_philos);
	if (!table->forks)
		ft_return_error(RED"Error: Malloc failed fork\n"RESET);
	table->philos->supervisor = malloc(sizeof(pthread_t) * table->num_philos);
	if (!table->philos->thread_id)
		ft_return_error(RED"Error: Malloc failed supervisor\n"RESET);
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
		table->philos[i].time_last_eat = 0;
		table->philos[i].eating_at_the_moment = 0;
		//pthread_mutex_init(&table->philos[i].is_done_eating, NULL);
		pthread_mutex_init(&table->philos[i].is_eating, NULL);
		i++;
	}
}

//Function to initialize and assign the forks in the table to the philosophers
//It assigns to specific philos a fork in their left and right hand
//It assigns the first philosopher the left fork first and then the right fork
void	ft_init_forks(t_philo *philo, t_fork *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		forks[i].id = i + 1;
		pthread_mutex_init(&forks[i].fork, NULL);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		if (philo[i].id == 1)
		{
			philo[i].left_fork = &forks[i];
			philo[i].right_fork = &forks[num_philos - 1];
		}
		else
		{
			philo[i].left_fork = &forks[i];
			philo[i].right_fork = &forks[i - 1];
		}
		i++;
	}
}

//Function to parse the input received from the user
//It checks if the time to die, eat and sleep are at least 60ms
//It populates the data structure with the input
//It also initializes the mutexes of the table
int	ft_parse_input(t_data *table, char **argv)
{
	table->num_philos = ft_atol(argv[1]);
	if (table->num_philos > MAX_PHILOS || table->num_philos < 1)
		return (ft_return_error(RED"ERROR: num of philos: 1 -> 200"RESET));
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (ft_return_error(RED"ERROR: time in ms, min 60"RESET));
	if (argv[5])
		table->num_times_to_eat = ft_atol(argv[5]);
	else
		table->num_times_to_eat = -1;
	table->end_simulation = FALSE;
	table->all_done_eating = FALSE;
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->simulation_done, NULL);
	pthread_mutex_init(&table->ready_to_go, NULL);
	return (SUCCESS);
}
//Function to initialize the values of the table
//It allocates memory for the philos and forks and 
//Initialize the philos and forks and assign the forks to the philos
int	ft_initialize(t_data *table, int argc, char **argv)
{
	if (ft_parse_input(table, argv) == ERROR)
		ft_return_error(RED"Error: Parsing input\n"RESET);
	ft_allocate_memory(table);
	ft_init_fork(table);
	ft_init_philos(table);
	//ft_assign_forks(table->philos, table->forks, table->num_philos);
	return (SUCCESS);
}
