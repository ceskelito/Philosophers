/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:22:11 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/09 17:58:41 by rceschel         ###   ########.fr       */
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
			printf("Argument syntax error");
			return (-1);
		}
		num = (num * 10) + (str[i] - '0');
	}
	return (num);
}

// Check the value of the input parameters
static int	check_values(int argc, unsigned long *args)
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
bool	input_is_valid(int argc, char **argv, unsigned long *rules)
{
	int	i;

	if (!(argc == MAX_ARGS || argc == MAX_ARGS - 1))
		return (false);
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
