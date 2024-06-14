/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:27:03 by luifer            #+#    #+#             */
/*   Updated: 2024/06/14 12:39:50 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_create_philos(t_data *table);
static int	ft_create_supervisor(t_data *table);

//Function to start the simulation
//It creates the threads for the philosophers and check for possible errors
//It joins the threads and check for possible errors
//It returns SUCCESS if everything went well and ERROR otherwise
int	ft_start_simulation(t_data *table)
{
	int	i;

	ft_create_philos(table);
	ft_create_supervisor(table);
	ft_switch_mtx(&table->all_ready_mtx, &table->all_philos_ready, SI);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	ft_switch_mtx(&table->finished_mtx, &table->end_simulation, SI);
	pthread_join(table->philo_thread, NULL);
	return (SUCCESS);
}

//Function to create the threads for the philosophers
static int	ft_create_philos(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL,
				ft_dinner_routine, &table->philos[i]))
			ft_return_error(RED"Error creating philosopher thread"RESET);
		i++;
	}
	return (SUCCESS);
}

//Function to create the supervisor thread
static int	ft_create_supervisor(t_data *table)
{
	if (pthread_create(&table->philo_thread, NULL,
			ft_supervise, table))
		ft_return_error(RED"Error creating supervisor thread"RESET);
	return (SUCCESS);
}
