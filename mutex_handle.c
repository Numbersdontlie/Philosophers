/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:09:56 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/06 12:28:16 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

//Function to initialize the mutexes of the table
//It initializes the mutex of print, start, simulation_done, all_ready and finished
void	ft_init_mtx_table(pthread_mutex_t *mtx, t_data *table)
{
	if (pthread_mutex_init(mtx, NULL))
		ft_clean_exit(table, RED"Error creating mutex"RESET);
}
