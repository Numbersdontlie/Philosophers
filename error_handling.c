/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:24:01 by luifer            #+#    #+#             */
/*   Updated: 2024/06/05 09:59:26 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to return an error message
int	ft_return_error(char *str)
{
	printf("%s\n", str);
	return (ERROR);
}

//Function to clean the memory and exit the program
//It destroys the mutex and frees the memory of the table
int	ft_clean_exit(t_data *table, char *str)
{
	printf("%s\n", str);
	ft_destroy_mutex(table);
	ft_free_memory(table);
	return (ERROR);
}

//Function to free the memory allocated 
//for the forks and the philosophers
//It also frees the memory of the table
void	ft_free_memory(t_data *table)
{
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	free(table);
}
