/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:58:27 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/12 16:37:00 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to check if a string is a positive number
//It returns an error if the string is not a positive number
static int	ft_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '0')
		return (ft_return_error("ERROR: Invalid number"));
	while (str[i])
	{
		if (str[i] == '-' || (str[i] < '0' || str[i] > '9'))
			return (ft_return_error("Insert a positive number"));
		i++;
	}
	if (i > 10)
		return (ft_return_error("ERROR: Number out of range"));
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

	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < time_milliseconds)
		usleep(400);
	return (SUCCESS);
}

//Function to get the current time in milliseconds
//It uses gettimeofday to get the time in seconds and microseconds
long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//Function to compare two strings
int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((size != '\0') && (*str1 != '\0') && (*str1 == *str2))
	{
		str1++;
		str2++;
		size--;
	}
	if (size != '\0')
		return (*str1 - *str2);
	else
		return (0);
}
