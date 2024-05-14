/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:23:31 by lperez-h          #+#    #+#             */
/*   Updated: 2024/05/14 15:01:50 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to check if a philosopher has died
//It checks if the time since the last eat is greater than the time to die
//If the philosopher has finished eating it returns FALSE
int	ft_check_die(t_philo *philo)
{
	long	time;
	long	dying_time;

	if (ft_check_mutex(&philo->is_done_eating, &philo->done_eating) == TRUE)
		return (FALSE);
	dying_time = philo->data->time_to_die;
	pthread_mutex_lock(&philo->is_eating);
	time = ft_get_time() - philo->time_last_eat;
	if (time >= dying_time)
	{
		pthread_mutex_unlock(&philo->is_eating);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->is_eating);
	return (FALSE);
}

//Function to monitor the philosophers
void	*ft_supervise(void *ptr)
{
	t_data	*table;
	int		i;

	table = (t_data *)ptr;
	while (ft_finish(table) == FALSE)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (ft_check_die(&table->philos[i]) == TRUE)
			{
				ft_switch_mutex(&table->simulation_done, &table->end_simulation, TRUE);
				ft_put_message(&table->philos[i], "died");
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
