/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:16:11 by luifer            #+#    #+#             */
/*   Updated: 2024/05/22 23:11:48 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to make a philosopher to grab a fork
//Modulus is used to make the philosopher with even id to take the right fork first
//and the philosopher with odd id to take the left fork first
void	ft_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		ft_put_msg(philo, YELLOW"has taken a fork"RESET);
		pthread_mutex_lock(&philo->left_fork->fork);
		ft_put_msg(philo, YELLOW"has taken a fork"RESET);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		ft_put_msg(philo, YELLOW"has taken a fork"RESET);
		pthread_mutex_lock(&philo->right_fork->fork);
		ft_put_msg(philo, YELLOW"has taken a fork"RESET);
	}
}

//Function to make a philosopher to eat
//It call the function to take the forks, lock the mutex to eat 
//update the last meal time and the number of times it has eaten, 
//it sleep and then release the forks
void	ft_philo_eat(t_philo *philo)
{
	ft_take_fork(philo);
	pthread_mutex_lock(&philo->philo_status);
	philo->eating_at_the_moment = TRUE;
	ft_put_msg(philo, YELLOW"is eating"RESET);
	philo->eat_count++;
	ft_sleep(philo->data->time_to_eat);
	ft_get_last_eat(philo);
	philo->eating_at_the_moment = FALSE;
	pthread_mutex_unlock(&philo->philo_status);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
	ft_put_msg(philo, GREEN"is sleeping"RESET);
	ft_sleep(philo->data->time_to_sleep);
	if (philo->data->num_times_to_eat == philo->eat_count)
		ft_switch_mutex(&philo->is_done_eating, &philo->done_eating, TRUE);
}

//Function to recreate the simulation
//with just one philosopher
void	ft_single_philo(t_data *table)
{
	table->start_time = ft_get_time();
	ft_put_msg(table->philos[0], YELLOW"has taken a fork"RESET);
	ft_sleep(table->time_to_die);
	ft_put_msg(table->philos[0], RED"died"RESET);
	ft_free_memory(table);
}
