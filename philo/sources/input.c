/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:22:11 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/12 15:00:58 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static bool	is_space(char c)
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
static bool	are_values_valids(int argc, long int *args)
{	
	int	i;

	i = 0;
	while (i < argc)
	{
		if ((args[i] < 0) || ((args[i] == 0) && (i != e_meals_to_eat)))
			return (false);
		i++;
	}
	return (true);
}

// Validates the input parameters, sargves their values in an array
bool	input_is_valid(int argc, char **argv, long int *rules)
{
	int	i;

	if (!(argc == MAX_ARGS || argc == MAX_ARGS - 1))
		return (ft_write(2, "Wrong number of arguments\n\0"),
				false);
	if (argc != MAX_ARGS)
		rules[e_meals_to_eat] = -1;
	i = 0;
	while (i < argc)
	{
		rules[i] = philo_atoi(argv[i]);
		i++;
	}
	return (are_values_valids(argc, rules));
}
