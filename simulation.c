/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:27:03 by luifer            #+#    #+#             */
/*   Updated: 2024/05/31 16:08:13 by lperez-h         ###   ########.fr       */
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
		if (pthread_create(&table->philos[0].thread_id, NULL, ft_single_philo, &table->philos[0]))
			return (ft_return_error("Error creating thread"));
	}
	else
	{
		while (i < table->num_philos)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL, ft_run_simulation, &table->philos[i]))
				return (ft_return_error("Error creating thread"));
			i++;
		}
	}
	if (pthread_create(&table->supervisor, NULL, ft_supervise, table))
		return (ft_return_error("Error creating supervisor"));
	ft_switch_mutex(&table->ready_to_go, &table->all_ready_to_start, TRUE);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	ft_switch_mutex(&table->simulation_done, &table->end_simulation, TRUE);
	pthread_join(table->supervisor, NULL);
	return (SUCCESS);
}

//Function to start to run the simulation
//It creates the threads for the supervisor of simulation
void	*ft_run_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (ft_check_mutex(&philo->data->ready_to_go, &philo->data->all_ready_to_start) == FALSE)
		usleep(180);
	if (philo->id % 2 == 1)
		ft_sleep(1);
	while (ft_check_end(philo->data) == FALSE)
	{
		ft_philo_eat(philo);
		if (ft_check_mutex(&philo->is_done_eating, &philo->done_eating) == TRUE)
			return (NULL);
		if (ft_check_end(philo->data) == FALSE)
			ft_sleep(philo->data->time_to_sleep);
		ft_put_msg(philo, "is thinking");
	}
	return (NULL);
}
