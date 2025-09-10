/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:22:11 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/10 12:49:05 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_space(char c)
{
	if (c == ' ' || (c == '\f') || (c == '\n'))
		return (1);
	else if (c == '\r' || (c == '\t') || (c == '\v'))
		return (1);
	return (0);
}

// A smaller atoi, with the necessary only for this project
static int	philo_atoi(const char *str)
{
	int	i;
	int	num;

	while (is_space(*str))
		str++;
	num = 0;
	i = -1;
	while (str[++i])
	{
		if (!is_num(str[i]))
		{
			ft_write(2, "Argument syntax error\n\0");
			return (-1);
		}
		num = (num * 10) + (str[i] - '0');
	}
	return (num);
}

// Check the value of the input parameters
static int	check_values(int argc, long int *args)
{	
	int	i;

	i = 0;
	while (i < argc)
	{
		if ((args[i] == 0) && (i != MAX_ARGS - 1))
			return (-1);
		i++;
	}
	return (0);
}

// Validates the input parameters, sargves their values in an array
bool	input_is_valid(int argc, char **argv, long int *rules)
{
	int	i;

	if (!(argc == MAX_ARGS || argc == MAX_ARGS - 1))
	{
		ft_write(2, "Wrong number of arguments\n\0");
		return (false);
	}
	i = 0;
	while (i < argc)
	{
		rules[i] = philo_atoi(argv[i]);
		i++;
	}
	if (!check_values(argc, rules) == 0)
		return (false);
	return (true);
}
