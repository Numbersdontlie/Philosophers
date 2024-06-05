/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:00 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/05 23:36:38 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*table;

	if (argc > MAX_PHILOS || argc < 1)
		ft_return_error(RED"Error: philosophers between 1 --> 200"RESET);
	if (argc == 5 || argc == 6)
	{
		table = (t_data *)malloc(sizeof(t_data));
		if (!table)
			return (ERROR);
		if (ft_check_input(argv) == ERROR)
			printf(RED"Error: not numeric values"RESET);
		if (ft_parse_input(table, argc, argv) == ERROR)
			return (ft_return_error(RED"Error: Invalid input to simulation"RESET));
		if (ft_initialize_data(table, argc, argv) == ERROR)
			return (ft_return_error(RED"Error: Initialization failed"RESET));
		if (table->num_philos == 1)
			ft_single_philo(table->philos);
		else
			ft_start_simulation(table);
		printf(YELLOW"Simulation finished\n"RESET);
		ft_destroy_mutex(table);
		ft_free_memory(table);
	}
	return (SUCCESS);
}
