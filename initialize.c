/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:57:56 by luifer            #+#    #+#             */
/*   Updated: 2024/05/07 16:40:03 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to initialize the philosophers in the table
//It assigns to each philosopher: the table, the id, a flag to 
//know when is done eating, the numeber of times it has eaten, 
//the time of last eat, the mutex to know when is done eating,
//the mutex to know when is eating, and assign forks.
void	ft_init_philos(t_data *table)
{
	int		i;
	t_philo	*philo;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		ft_clean_exit(table, RED"Error: Malloc failed\n"RESET);
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].data = table;
		table->philos[i].id = i + 1;
		table->philos[i].done_eating = 0;
		table->philos[i].eat_count = 0;
		table->philos[i].time_last_eat = 0;
		pthread_mutex_init(&table->philos[i].is_done_eating, NULL);
		pthread_mutex_init(&table->philos[i].is_eating, NULL);
		i++;
	}
	ft_assign_forks(&table->philos[i], table->forks, table->num_philos);
}

//Function to initialize the forks in the table
//It assigns to each philo a fork in their left and right hand
//
void	ft_assign_forks(t_philo *philo, t_fork *forks, int num_philos)
{
	int	i;

	i = 1;
	while (i < num_philos)
	{
		if (philo->id == 1)
		{
			philo->left_fork = &forks[philo[i].id];
			philo->right_fork = &forks[num_philos];
		}
		else
		{
			philo->left_fork = &forks[philo[i].id];
			philo->right_fork = &forks[philo[i].id - 1];
		}
		i++;
	}
}

