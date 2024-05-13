/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:58:27 by lperez-h          #+#    #+#             */
/*   Updated: 2024/05/13 11:12:01 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to convert a string to a long
int	ft_atol(char *nptr)
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

//Function to check if a string is a positive number
//It returns an error if the string is not a positive number
static int	ft_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '0')
		return (ft_return_error(RED"ERROR: Invalid number"RESET));
	while (str[i])
	{
		if (str[i] == '-' || (str[i] < '0' || str[i] > '9'))
			return (ft_return_error(RED"Insert a positive number"RESET));
		i++;
	}
	if (i > 10)
		return (ft_return_error(RED"ERROR: Number out of range"RESET));
	return (SUCCESS);
}

//Function to check if all the arguments received from user 
//are positive numbers
int	ft_check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_all_digit(argv[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

//Function to get the start time of the simulation
//it receives the time in milliseconds and check that 
//the time transcurred since the start is less than the time
//received and sleep 100ms when true
int	ft_sleep(size_t time_milliseconds)
{
	size_t	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_milliseconds)
		usleep(100);
	return (SUCCESS);
}

