/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:16:11 by luifer            #+#    #+#             */
/*   Updated: 2024/05/21 12:10:56 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_single_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->data->simulation_done == FALSE)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo->data->time_to_eat);
		ft_think(philo);
	}
}


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
	pthread_mutex_lock(&philo->is_eating);
	philo->eating_at_the_moment = TRUE;
	ft_put_msg(philo, YELLOW"is eating"RESET);
	philo->eat_count++;
	ft_sleep(philo->data->time_to_eat);
	philo->time_last_eat = ft_get_time();
	philo->eating_at_the_moment = FALSE;
	pthread_mutex_unlock(&philo->is_eating);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
	if (philo->data->num_times_to_eat == philo->eat_count)
		ft_switch_mutex(&philo->is_done_eating, &philo->done_eating, TRUE);
	ft_put_msg(philo, GREEN"is sleeping"RESET);
	ft_sleep(philo->data->time_to_sleep);
}
