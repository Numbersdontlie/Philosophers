/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:23:31 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/14 12:40:59 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to check if a philosopher has died
//It checks if the time since the last eat is greater than the time to die
//If the philosopher has finished eating it returns NO
int	ft_check_die(t_philo *philo)
{
	long	time;
	long	dying;

	if (ft_still_there(&philo->philo_done_mtx, &philo->done_eating) == SI)
		return (NO);
	dying = philo->data->time_to_die;
	pthread_mutex_lock(&philo->philo_last_mtx);
	time = ft_get_time() - philo->time_last_eat;
	if (time >= dying)
	{
		pthread_mutex_unlock(&philo->philo_last_mtx);
		return (SI);
	}
	pthread_mutex_unlock(&philo->philo_last_mtx);
	return (NO);
}

//Function to monitor the philosophers
//It checks if a philosopher has died and if so it ends the simulation
//It returns NULL
void	*ft_supervise(void *ptr)
{
	t_data	*table;
	int		i;

	table = (t_data *)ptr;
	while (ft_still_there(&table->finished_mtx, &table->end_simulation) == NO)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (ft_check_die(&table->philos[i]) == SI)
			{
				ft_switch_mtx(&table->finished_mtx, &table->end_simulation, SI);
				ft_put_msg(&table->philos[i], "died");
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

//Function to print a message
//It locks the mutex to print the message and unlock it
//It prints the message with the time, the philosopher id and the message
//it also check the message content to act accordingly
void	ft_put_msg(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_mtx);
	time = ft_get_time() - philo->data->start_time;
	if (ft_still_there(&philo->data->finished_mtx,
			&philo->data->end_simulation) == NO)
	{
		if (ft_strncmp("is eating", str, 9) == 0)
			printf(GREEN"%ld %d %s\n"RESET, time, philo->id, str);
		else
			printf("%ld %d %s\n", time, philo->id, str);
	}
	else if (ft_strncmp("died", str, 4) == 0)
		printf(RED"%ld %d %s\n"RESET, time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mtx);
}
