/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:16:11 by luifer            #+#    #+#             */
/*   Updated: 2024/06/05 01:19:12 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to make a philosopher to eat
//It call the function to take the forks, lock the mutex to eat 
//update the last meal time and the number of times it has eaten, 
//it sleep and then release the forks
void	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	ft_put_msg(philo, GREEN"has taken a fork"RESET);
	pthread_mutex_lock(&philo->second_fork->fork);
	ft_put_msg(philo, GREEN"has taken a fork"RESET);
	ft_put_msg(philo, YELLOW"is eating"RESET);
	pthread_mutex_lock(&philo->philo_status);
	philo->time_last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->philo_status);
	ft_sleep(philo->data->time_to_eat);
	philo->eat_count++;
	if (philo->eat_count == philo->data->num_times_to_eat)
	{
		ft_put_msg(philo, GREEN"got all the meals"RESET);
		pthread_mutex_lock(&philo->philo_status);
		philo->done_eating = TRUE;
		pthread_mutex_unlock(&philo->philo_status);
		pthread_mutex_lock(&philo->data->finished_mtx);
		philo->data->all_done_eating++;
		pthread_mutex_unlock(&philo->data->finished_mtx);
	}
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

//Function to recreate the simulation
//with just one philosopher, it will grab a fork and sleep
//until it dies
void	*ft_single_philo(t_philo *philo)
{
	ft_put_msg(philo, YELLOW"has taken a fork"RESET);
	ft_sleep(philo->data->time_to_die);
	ft_put_msg(philo, "died");
}

//Function to display the number of meals eaten by each philosopher
//It locks the mutex to print the message
//It iterates over the philosophers and print the number of meals eaten
void	ft_put_meals(t_data *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->print_mtx);
	while (i < table->num_philos)
	{
		printf("Philo %d has eaten %d times\n", table->philos[i].id, table->philos[i].eat_count);
		i++;
	}
	pthread_mutex_unlock(&table->print_mtx);
}

//Function to simulate a philosopher thinking
void	ft_philo_thinking(t_philo *philo)
{
	ft_put_msg(philo, "is thinking");
	if (ft_check_end(philo->data) == FALSE)
		ft_sleep(philo->data->time_to_think);
}
