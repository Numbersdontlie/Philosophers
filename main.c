/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:00 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/13 19:07:16 by lperez-h         ###   ########.fr       */
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
			return (1);
		if (ft_check_input(argv) == ERROR)
			return (ft_return_error(RED"Error: not numeric values"RESET));
		if (ft_parse_input(table, argc, argv) == ERROR)
			return (ft_return_error(RED"Error: Invalid input to simulation"RESET));
		if (ft_initialize_data(table) == ERROR)
			return (ft_return_error(RED"Error: Initialization failed"RESET));
		if (table->num_philos == 1)
			ft_start_simulation_single(table);
		else
			ft_start_simulation(table);
		ft_put_meals(table);
		ft_destroy_mutex(table);
		ft_free_memory(table);
	}
	else
		ft_return_error(RED"Error: ./philo 5 800 200 200 [8]\n"RESET);
	return (SUCCESS);
}
