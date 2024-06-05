/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:09:56 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/05 09:59:30 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to safely initialize a mutex
//It checks if the mutex was initialized correctly
//If not, it calls the function to clean the memory and exit the program
//It increments the counter of mutexes in the table
void	ft_initialize_mutex(pthread_mutex_t *mutex, t_data *table)
{
	if (pthread_mutex_init(mutex, NULL))
		ft_clean_exit(table, RED"Error: Mutex init failed\n"RESET);
	table->counter++;
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
		pthread_mutex_destroy(&table->philos[i].philo_status);
		i++;
	}
	pthread_mutex_destroy(&table->print_mtx);
	pthread_mutex_destroy(&table->all_ready_mtx);
	pthread_mutex_destroy(&table->finished_mtx);
	pthread_mutex_destroy(&table->start_mtx);
	pthread_mutex_destroy(&table->simulation_done_mtx);
}

