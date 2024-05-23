/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:09:56 by lperez-h          #+#    #+#             */
/*   Updated: 2024/05/23 12:18:30 by lperez-h         ###   ########.fr       */
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

//Function to check if the simulation has finished
int	ft_check_end(t_data *table)
{
	int	i;

	i = ft_check_mutex(&table->simulation_done, &table->end_simulation);
	return (i);
}

//Function to get the last time a philosopher ate
void	ft_get_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_status);
	philo->time_last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->philo_status);
}
