/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:24:01 by luifer            #+#    #+#             */
/*   Updated: 2024/06/14 12:44:24 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atol(char *nptr);

//Function to convert a string to a long
static int	ft_atol(char *nptr)
{
	long	result;

	result = 0;
	while (((*nptr >= 9) && (*nptr <= 13)) || (*nptr == 32))
		nptr++;
	if (*nptr == 43)
		nptr++;
	while ((*nptr >= 48) && (*nptr <= 57))
	{
		result = ((result * 10) + (*nptr - 48));
		nptr++;
	}
	return (result);
}

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

//Function to parse the input received from the user
//It checks if the time to die, eat and sleep are at least 60ms
//It populates the data structure with the input
//It also initializes the mutexes of the table
int	ft_parse_input(t_data *table, int argc, char **argv)
{
	table->num_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->num_times_to_eat = ft_atol(argv[5]);
	else
		table->num_times_to_eat = -1;
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (ft_return_error("ERROR: time in ms, min 60"));
	if (argc > MAX_PHILOS || argc < 1)
		ft_return_error(RED"Error: philosophers between 1 --> 200"RESET);
	return (SUCCESS);
}
