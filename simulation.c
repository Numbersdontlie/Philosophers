/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:27:03 by luifer            #+#    #+#             */
/*   Updated: 2024/06/05 01:34:29 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to start the simulation
//It creates the threads for the philosophers and check for possible errors
//It joins the threads and check for possible errors
//It returns SUCCESS if everything went well and ERROR otherwise
void	ft_start_simulation(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &ft_run_simulation, &table->philos[i]))
			ft_clean_exit(table, RED"Error creating philosopher thread"RESET);
		i++;
	}
	pthread_mutex_lock(&table->all_ready_mtx);
	table->all_philos_ready = FALSE;
	pthread_mutex_unlock(&table->all_ready_mtx);
	ft_supervise(table);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL))
			ft_clean_exit(table, RED"Error joining philosopher thread"RESET);
		i++;
	}
}

//Function to start to run the simulation
//It creates the threads for the supervisor of simulation
void	*ft_run_simulation(void *ptr)
{
	t_philo	*philo;


	philo = (t_philo *)ptr;
	while (ft_coordinate_start(philo->data) == SUCCESS)
		;
	if (philo->time_last_eat == 0)
	{
		pthread_mutex_lock(&philo->philo_status);
		philo->time_last_eat = ft_get_time();
		pthread_mutex_unlock(&philo->philo_status);
		pthread_mutex_lock(&philo->data->start_mtx);
		philo->data->ready_to_begin++;
		pthread_mutex_unlock(&philo->data->start_mtx);
	}
	
	while (ft_check_end(philo->data) == FALSE && philo->done_eating == 0)
	{
		ft_philo_eat(philo);
		ft_put_msg(philo, YELLOW"is sleeping"RESET);
		ft_sleep(philo->data->time_to_sleep);
		ft_put_msg(philo, YELLOW"is thinking"RESET);
	}
	return (NULL);
	return (NULL);
}
