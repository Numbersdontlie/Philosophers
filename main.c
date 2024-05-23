/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:00 by lperez-h          #+#    #+#             */
/*   Updated: 2024/05/23 11:55:18 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*table;

	if (argc == 5 || argc == 6)
	{
		table = (t_data *)malloc(sizeof(t_data));
		if (!table)
			return (ERROR);
		if (ft_check_input(argv) == ERROR)
			return (ft_return_error("Error: Invalid input"));
		if (ft_parse_input(table, argv) == ERROR)
			return (ft_return_error("Error: Invalid input"));
		if (ft_initialize(table, argv) == ERROR)
			return (ft_return_error("Error: Initialization failed"));
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