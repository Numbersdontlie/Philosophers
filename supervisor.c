/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:23:31 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/06 13:22:18 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to check if a philosopher has died
//It checks if the time since the last eat is greater than the time to die
//If the philosopher has finished eating it returns FALSE
int	ft_check_die(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->philo_status);
	if (philo->done_eating == ERROR)
	{
		pthread_mutex_unlock(&philo->philo_status);
		return (ERROR);
	}
	time = ft_get_time() - philo->time_last_eat;
	if (time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->simulation_done_mtx);
		philo->data->end_simulation = ERROR;
		pthread_mutex_unlock(&philo->data->simulation_done_mtx);
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%ld %d %s\n", ft_get_time() - philo->data->start_time, philo->id, "died");
		pthread_mutex_unlock(&philo->data->print_mtx);
		pthread_mutex_unlock(&philo->philo_status);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&philo->philo_status);
	return (ERROR);
}

//Function to coordinate the start of the threads
//it wait untill all the philos have the last meal 
//correctly setup and then it starts the simulation
int	ft_coordinate_start(t_data *table)
{
	pthread_mutex_lock(&table->start_mtx);
	if (table->ready_to_begin == table->num_philos)
	{
		pthread_mutex_unlock(&table->start_mtx);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&table->start_mtx);
	return (ERROR);
}

//Function to start the supervisor of the simulation
//it locks the mutex to check if all the philos are ready to begin
int	ft_start_supevisor(t_data *table)
{
	pthread_mutex_lock(&table->start_mtx);
	if (table->ready_to_begin < table->num_philos)
	{
		pthread_mutex_unlock(&table->start_mtx);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&table->start_mtx);
	return (ERROR);
}

//Function to check if all the philos finished eating 
//it also check if the simulation has finished cause someone died
int	ft_check_end(t_data *table)
{
	pthread_mutex_lock(&table->finished_mtx);
	if (table->all_done_eating == table->num_philos)
	{
		pthread_mutex_unlock(&table->finished_mtx);
		return (ERROR);
	}
	pthread_mutex_unlock(&table->finished_mtx);
	pthread_mutex_lock(&table->simulation_done_mtx);
	if (table->end_simulation == ERROR)
	{
		pthread_mutex_unlock(&table->simulation_done_mtx);
		return (ERROR);
	}
	pthread_mutex_unlock(&table->simulation_done_mtx);
	return (SUCCESS);
}

//Function to monitor the philosophers
//It checks if a philosopher has died and if so it ends the simulation
//It returns NULL
void	ft_supervise(t_data *table)
{
	int	i;

	while (ft_start_supevisor(table) == SUCCESS)
		;
	while (ft_check_end(table) == SUCCESS)
	{
		i = 0;
		while (ft_check_end(table) == SUCCESS && i < table->num_philos)
		{
			if (ft_check_die(&table->philos[i]) == SUCCESS)
				return ;
			i++;
		}
	}
}
