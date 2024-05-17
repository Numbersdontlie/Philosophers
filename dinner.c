/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:28:43 by lperez-h          #+#    #+#             */
/*   Updated: 2024/05/17 18:03:41 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to simulate the dinner of a single philosopher
//It locks the mutex to start the simulation
//It gets the last time the philosopher ate
void	ft_single_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (ft_check_mutex(&philo->data->ready_to_go, &philo->data->simulation_done) == FALSE)
		ft_usleep(150);
	ft_get_last_eat(philo);
	pthread_mutex_lock(&philo->left_fork->fork);
	ft_put_msg(philo, GREEN"has taken a fork"RESET);
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (NULL);
}

//Function to simulate the dinner of a philosopher
//It locks the mutex (left + right fork), get the last meal
//It simulates the eating time, unlock the mutex and increase the 
//number of times the philosopher has eaten
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	ft_put_msg(philo, GREEN"has taken a fork"RESET);
	if (ft_check_end(philo->data) == TRUE)
		return ;
	pthread_mutex_lock(&philo->right_fork->fork);
	ft_put_msg(philo, GREEN"has taken a fork"RESET);
	ft_get_last_eat(philo);
	ft_put_msg(philo, GREEN"is eating"RESET);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	philo->eat_count++;
	if (philo->eat_count == philo->data->num_times_to_eat)
		ft_switch_mutex(&philo->is_done_eating, &philo->done_eating, TRUE);
}

void	ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->data->ready_to_go);
}