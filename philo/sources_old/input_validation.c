/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:39:58 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/09 16:00:28 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

static int	is_space(char c)
{
	if (c == ' ' || (c == '\f') || (c == '\n'))
		return (1);
	else if (c == '\r' || (c == '\t') || (c == '\v'))
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	nb;

	while (is_space(*str))
		str++;
	nb = 0;
	sign = 1;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	i = 0;
	while (str[i] >= '0' && (str[i] <= '9'))
	{
		if (i != 0)
			nb *= 10;
		nb += (str[i++] - '0');
	}
	return (nb * sign);
}

// Check the value of the input parameters
static int	check_value(int ac, int *arg)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (arg[i] < 0 || (arg[i] == 0 && i != 4))
			return (-1);
		i++;
	}
	return (0);
}

// Convert input parameters as integers
static int	atoi_input(int ac, char **av, int *arg)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (-1);
			j++;
		}
		arg[i] = ft_atoi(av[i]);
		i++;
	}
	return (0);
}

// Validates the input parameters, saves their values in an array
bool	input_is_valid(int ac, char **av, int *arg)
{
	ac -= 1;
	av += 1;
	return (
		(ac == 4 || ac == 5)
		&& (atoi_input(ac, av, arg) == 0)
		&& (check_value(ac, arg) == 0)
	);
}
