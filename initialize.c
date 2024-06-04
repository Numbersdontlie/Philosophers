/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:57:56 by luifer            #+#    #+#             */
/*   Updated: 2024/06/05 00:00:48 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
void	ft_allocate_memory(t_data *table)
{
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		ft_return_error("Error: Malloc failed philo\n");
	table->forks = malloc(sizeof(t_fork) * table->num_philos);
	if (!table->forks)
		ft_return_error("Error: Malloc failed fork\n");
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
		table->philos[i].done_eating = 0;
		ft_initialize_mutex(&table->philos[i].philo_status, table);
		i++;
	}
	ft_assign_forks(table->philos, table->forks, table->num_philos);
}

//Function to initialize the forks in the table
//It assigns to each fork: the id and the mutex
//It initializes the mutex of the fork
void	ft_init_forks(t_data *table)
{
	t_fork	*forks;
	int	i;

	i = 0;
	forks = table->forks;
	while (i < table->num_philos)
	{
		forks[i].id = i + 1;
		ft_initialize_mutex(&forks[i].fork, table);
		i++;
	}
}

//Function to initialize the values of the table
//It allocates memory for the philos and forks and 
//Initialize the philos and forks and assign the forks to the philos
int	ft_initialize_data(t_data *table, int argc , char **argv)
{
	if (ft_parse_input(table, argc, argv) == ERROR)
		ft_return_error("Error: Parsing input\n");
	table->forks = NULL;
	table->philos = NULL;
	table->start_time = 0;
	table->end_simulation = 0;
	table->all_done_eating = 0;
	table->all_philos_ready = 0;
	table->ready_to_begin = 0;
	table->counter = 0;
	ft_initialize_mutex(&table->all_ready_mtx, table);
	ft_initialize_mutex(&table->start_mtx, table);
	ft_initialize_mutex(&table->end_mtx, table);
	ft_initialize_mutex(&table->print_mtx, table);
	ft_initialize_mutex(&table->simulation_done_mtx, table);
	ft_allocate_memory(table);
	ft_init_forks(table);
	ft_init_philos(table);
	return (SUCCESS);
}

//Function to assign the forks to the philosophers
//odd philos start with left fork, even philos start with right fork
void	ft_assign_forks(t_philo *philo, t_fork *fork, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (philo[i].id % 2 != 0)
		{
			philo[i].first_fork = &fork[i];
			if (i == 0)
				philo[i].second_fork = &fork[num_philo - 1];
			else
				philo[i].second_fork = &fork[i - 1];
			i++;
		}
		else
		{
			philo[i].first_fork = &fork[i - 1];
			philo[i].second_fork = &fork[i];
			i++;
		}
	}
}
