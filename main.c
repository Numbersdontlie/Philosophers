/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:46:00 by lperez-h          #+#    #+#             */
/*   Updated: 2024/05/06 23:09:18 by luifer           ###   ########.fr       */
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
			return(ERROR);
		if (ft_check_input(argv) == ERROR)
			return (ft_return_error(RED"Error: Invalid input"RESET));
		if (ft_parse_input(table, argv) == ERROR)
			return (ft_return_error(RED"Error: Invalid input"RESET));
		if ()
		
		//ft_parse_input(&table, argv); ToDo
		//ft_data_init(&table); ToDo
		//ft_feed_philos(&table); ToDo
		//ft_clean(&table); ToDo
	}
	else
	{
		ft_exit_simulation(RED"Error: Wrong number of arguments"RESET);
	}
}