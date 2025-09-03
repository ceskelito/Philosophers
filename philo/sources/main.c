/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:12:35 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/03 18:00:36 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	int	arg[5];

	if (!validate_input(ac, av, (int **)&arg))
		return (-1);
	else
		printf("DAJEEEEEEEE\n"); //DEBUG
}
