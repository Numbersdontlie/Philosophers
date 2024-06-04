/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:00 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/05 01:28:05 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*table;

	if (ft_check_input(argc, argv) == SUCCESS)
	{
		printf(GREEN"Arguments are numeric\n"RESET);
		table = (t_data *)malloc(sizeof(t_data));
		if (!table)
			return (ERROR);
		if (ft_parse_input(table, argv) == ERROR)
			return (ft_return_error(RED"Error: Invalid input to simulation"RESET));
		if (ft_initialize_data(table, argc, argv) == ERROR)
			return (ft_return_error(RED"Error: Initialization failed"RESET));
		table->start_time = ft_get_time();
		if (table->num_philos == 1)
			ft_single_philo(table);
		else
			ft_start_simulation(table);
		ft_put_meals(table);
		ft_destroy_mutex(table);
		free(table->philos);
		free(table->forks);
		free(table);
	}
	else
		printf("Error: Wrong number of arguments");
	return (SUCCESS);
}