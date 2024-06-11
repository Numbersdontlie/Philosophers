/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:23:31 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/11 18:17:08 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to check if a philosopher has died
//It checks if the time since the last eat is greater than the time to die
//If the philosopher has finished eating it returns FALSE
int	ft_check_die(t_philo *philo)
{
	long	time;
	long	dying;

	if (ft_still_there(&philo->philo_done_mtx, &philo->done_eating) == TRUE)
		return (FALSE);
	dying = philo->data->time_to_die;
	pthread_mutex_lock(&philo->philo_last_mtx);
	time = ft_get_time() - philo->time_last_eat;
	if (time >= dying)
	{
		pthread_mutex_unlock(&philo->philo_last_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->philo_last_mtx);
	return (FALSE);
}


//Function to monitor the philosophers
//It checks if a philosopher has died and if so it ends the simulation
//It returns NULL
void	*ft_supervise(void *ptr)
{
	t_data	*table;
	int		i;

	table = (t_data *)ptr;
	while (ft_still_there(&table->finished_mtx, &table->end_simulation) == FALSE)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (ft_check_die(&table->philos[i]) == TRUE)
			{
				ft_switch_mtx(&table->finished_mtx, &table->end_simulation, TRUE);
				ft_put_msg(&table->philos[i], "died");
				return (NULL);
			}
			i++;
		}
	}
}

