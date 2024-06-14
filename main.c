/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:00 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/14 12:51:28 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_single_philo(void *ptr);
static int	ft_create_single_philo(t_data *table);

//Function to start the simulation with just one philosopher
int	ft_start_simulation_single(t_data *table)
{
	ft_create_single_philo(table);
	return (SUCCESS);
}

//Function to create a single philosopher
//it will create the thread for the philosopher and check for possible errors
static int	ft_create_single_philo(t_data *table)
{
	if (pthread_create(&table->philos[0].thread_id, NULL,
			ft_single_philo, &table->philos[0]))
		ft_return_error(RED"Error creating philosopher thread"RESET);
	ft_sleep(500);
	return (SUCCESS);
}

//Function to recreate the simulation
//with just one philosopher, it will set the starting point 
//will grab a fork and sleep until it dies. it will also clean the memory
static void	*ft_single_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->data->start_time = ft_get_time();
	ft_put_msg(philo, YELLOW"has taken a fork"RESET);
	ft_sleep(philo->data->time_to_die);
	ft_sleep(100);
	ft_put_msg(philo, "died");
	ft_clean_exit(philo->data, "died");
	return (NULL);
}

//Function to print the amount of meals
//each philosopher has eaten
void	ft_put_meals(t_data *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->print_mtx);
	while (i < table->num_philos)
	{
		printf(GREEN"%d has %d meals eaten\n"RESET,
			table->philos[i].id, table->philos[i].eat_count);
		i++;
	}
	pthread_mutex_unlock(&table->print_mtx);
}

int	main(int argc, char **argv)
{
	t_data	*table;

	if (argc == 5 || argc == 6)
	{
		table = (t_data *)malloc(sizeof(t_data));
		if (!table)
			return (1);
		if (ft_check_input(argv) == ERROR)
			return (ft_return_error(RED"Error: not numeric values"RESET));
		if (ft_parse_input(table, argc, argv) == ERROR)
			return (ft_return_error(RED
					"Error:Invalid input to simulation"RESET));
		if (ft_initialize_data(table) == ERROR)
			return (ft_return_error(RED"Error: Initialization failed"RESET));
		if (table->num_philos == 1)
			ft_start_simulation_single(table);
		else
			ft_start_simulation(table);
		ft_put_meals(table);
		ft_destroy_mutex(table);
		ft_free_memory(table);
	}
	else
		ft_return_error(RED"Error: ./philo 5 800 200 200 [8]\n"RESET);
	return (SUCCESS);
}
