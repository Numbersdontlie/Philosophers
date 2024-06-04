/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:09:56 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/05 00:27:11 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to check the status of a mutex
//It locks the mutex, reads the value and unlocks the mutex
void	ft_switch_mutex(pthread_mutex_t *mutex, int *value, int status)
{
	pthread_mutex_lock(mutex);
	*value = status;
	pthread_mutex_unlock(mutex);
}

//Function to check the status of a mutex
//It locks the mutex, reads the value and unlocks the mutex
//It returns the value of the mutex
int	ft_check_mutex(pthread_mutex_t *mutex, int *value)
{
	int	status;

	pthread_mutex_lock(mutex);
	status = *value;
	pthread_mutex_unlock(mutex);
	return (status);
}

//Function to get the last time a philosopher ate
void	ft_get_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_status);
	philo->time_last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->philo_status);
}

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
