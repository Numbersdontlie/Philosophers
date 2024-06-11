/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:27:03 by luifer            #+#    #+#             */
/*   Updated: 2024/06/11 18:14:45 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to start the simulation
//It creates the threads for the philosophers and check for possible errors
//It joins the threads and check for possible errors
//It returns SUCCESS if everything went well and ERROR otherwise
int	ft_start_simulation(t_data *table)
{
	int	i;

	i = 0;
	if (table->num_philos == 1)
	{
		if (pthread_create(&table->philos[0].thread_id, NULL,
				ft_single_philo, &table->philos[0]))
			ft_return_error(RED"Error creating philosopher thread"RESET);
	}
	else
	{
		while (i < table->num_philos)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL,
					ft_dinner_routine, &table->philos[i]))
				ft_return_error(RED"Error creating philosopher thread"RESET);
			i++;
		}
	}
	if (pthread_create(&table->philo_thread, NULL,
			ft_supervise, table))
		ft_return_error(RED"Error creating supervisor thread"RESET);
	ft_switch_mtx(&table->all_ready_mtx, &table->all_philos_ready, TRUE);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	ft_switch_mtx(&table->finished_mtx, &table->end_simulation, TRUE);
	pthread_join(table->philo_thread, NULL);
	return (SUCCESS);
}

//Function to recreate the simulation
//with just one philosopher, it will set the starting point 
//will grab a fork and sleep until it dies. it will also clean the memory
void	*ft_single_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->data->start_time = ft_get_time();
	ft_put_msg(philo, YELLOW"has taken a fork"RESET);
	ft_sleep(philo->data->time_to_die);
	ft_put_msg(philo, "died");
	ft_clean_exit(philo->data, "died");
	return (NULL);
}

//Function to print the amount of meals
//each philosopher has eaten
void	ft_print_meals(t_data *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->print_mtx);
	while (i < table->num_philos)
	{
		printf(GREEN"%d has %d meals eaten\n"RESET,
			table->philos[i].eat_count, table->philos[i].eat_count);
		i++;
	}
	pthread_mutex_unlock(&table->print_mtx);
}

