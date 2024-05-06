/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:40:31 by lperez-h          #+#    #+#             */
/*   Updated: 2024/05/06 17:24:02 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to parse the input received from the user
//It checks if the number of philosophers is between 1 and 200
//It checks if the time to die, eat and sleep are at least 60ms
//It populates the data structure with the input
int	ft_parse_input(t_data *table, char **argv)
{
	table->num_philos = ft_atol(argv[1]);
	if (table->num_philos > MAX_PHILOS || table->num_philos < 1)
		return (ft_return_error(RED"ERROR: num of philos: 1 -> 200"RESET));
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (ft_return_error(RED"ERROR: time in ms, min 60"RESET));
	if (argv[5])
		table->num_times_to_eat = ft_atol(argv[5]);
	else
		table->num_times_to_eat = -1;
	return (SUCCESS);
}
