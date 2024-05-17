/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:28:43 by lperez-h          #+#    #+#             */
/*   Updated: 2024/05/17 11:46:45 by lperez-h         ###   ########.fr       */
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

int	