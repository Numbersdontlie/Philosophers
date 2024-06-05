/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:58:27 by lperez-h          #+#    #+#             */
/*   Updated: 2024/06/05 15:40:16 by luifer           ###   ########.fr       */
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

//Function to print a message
void	ft_put_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	if (ft_check_end(philo->data) == ERROR)
		printf("%ld %d %s\n", ft_get_time()
			- philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mtx);
}
