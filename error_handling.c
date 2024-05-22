/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:24:01 by luifer            #+#    #+#             */
/*   Updated: 2024/05/22 21:20:04 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to return an error message
int	ft_return_error(char *str)
{
	printf("%s\n", str);
	return (ERROR);
}

//Function to free the allocated memory
//It frees the forks, the philosophers and the table holding the data of simulation
void	ft_free_memory(t_data *table)
{
	if (table->supervisor)
	{
		free(table->supervisor);
		table->supervisor = NULL;
	}
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	free(table);
}

//Function to destroy the mutexes
//It destroys the mutex of the forks and the philosophers
//It also destroys the mutex of the print, the ready_to_go and the simulation_done
void	ft_destroy_mutex(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		//pthread_mutex_destroy(&table->philos[i].is_done_eating);
		pthread_mutex_destroy(&table->philos[i].philo_status);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->ready_to_go);
	pthread_mutex_destroy(&table->simulation_done);
}

//Function to clean the memory and exit the program
//It destroys the mutex and frees the memory of the table
void	ft_clean_exit(t_data *table, char *str)
{
	printf("%s\n", str);
	ft_destroy_mutex(table);
	ft_free_memory(table);
	return (ERROR);
}
