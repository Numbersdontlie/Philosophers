/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:16:11 by luifer            #+#    #+#             */
/*   Updated: 2024/06/12 12:14:47 by luifer           ###   ########.fr       */
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
	if (ft_still_there(&philo->data->finished_mtx,
			&philo->data->end_simulation) == SI)
		return ;
	pthread_mutex_lock(&philo->second_fork->fork);
	ft_put_msg(philo, GREEN"has taken a fork"RESET);
	pthread_mutex_lock(&philo->philo_last_mtx);
	philo->time_last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->philo_last_mtx);
	ft_put_msg(philo, YELLOW"is eating"RESET);
	ft_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
	philo->eat_count++;
	if (philo->eat_count == philo->data->num_times_to_eat)
		ft_switch_mtx(&philo->philo_done_mtx, &philo->done_eating, SI);
}

//Function to make a philosopher to think
//It print the message and sleep
//if time to think is greater than 5, it will sleep 80% of the time
void	ft_thinking(t_philo *philo)
{
	ft_put_msg(philo, YELLOW"is thinking"RESET);
	if (ft_still_there(&philo->data->finished_mtx,
			&philo->data->end_simulation) == NO)
	{
		if (philo->data->time_to_think > 5)
			ft_sleep(philo->data->time_to_think * 0.8);
	}
}

//Function to create the dinner routine
//It will check that the simulation is still running
//it will check if the philo id is even or odd in order to make it wait
//to grab a fork. It will make the philo to eat, sleep and think
void	*ft_dinner_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (ft_still_there(&philo->data->all_ready_mtx,
			&philo->data->all_philos_ready) == NO)
		usleep(100);
	if (philo->id % 2 == 1)
		usleep(1);
	while (ft_still_there(&philo->data->finished_mtx, &philo->data->end_simulation) == NO)
	{
		ft_philo_eat(philo);
		ft_put_msg(philo, GREEN"is sleeping"RESET);
		if (ft_still_there(&philo->philo_done_mtx, &philo->done_eating) == SI)
			return (NULL);
		if (ft_still_there(&philo->data->finished_mtx, &philo->data->end_simulation) == NO)
			ft_sleep(philo->data->time_to_sleep);
		ft_thinking(philo);
	}
	return (NULL);
}
