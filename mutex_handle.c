/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:09:56 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/12 17:01:05 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to destroy the mutexes
//It destroys the mutex of the forks and the philosophers
//It also destroys the mutex of the print, the ready_to_go 
//and the simulation_done
void	ft_destroy_mutex(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		pthread_mutex_destroy(&table->philos[i].philo_done_mtx);
		pthread_mutex_destroy(&table->philos[i].philo_last_mtx);
		i++;
	}
	pthread_mutex_destroy(&table->print_mtx);
	pthread_mutex_destroy(&table->all_ready_mtx);
	pthread_mutex_destroy(&table->finished_mtx);
}

//Function to initialize the mutexes of the table
void	ft_init_mtx_table(pthread_mutex_t *mtx, t_data *table)
{
	if (pthread_mutex_init(mtx, NULL))
		ft_clean_exit(table, RED"Error creating mutex"RESET);
}

//Function to switch safely a mutex 
//it lock the mutex, write in the shared variable and unlock the mutex
void	ft_switch_mtx(pthread_mutex_t *mtx, int *value, int new_value)
{
	pthread_mutex_lock(mtx);
	*value = new_value;
	pthread_mutex_unlock(mtx);
}

//Function to check the value of a shared variable
//It lock the mutex, read the value and unlock the mutex
//it will be used to check if the simulation is still running
int	ft_still_there(pthread_mutex_t *mtx, int *value)
{
	int	ret;

	pthread_mutex_lock(mtx);
	ret = *value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	ft_get_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_last_mtx);
	philo->time_last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->philo_last_mtx);
}