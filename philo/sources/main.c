/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:12:35 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/04 18:50:14 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define CLEANUP __attribute__(cleanup(clean_memory))

static int	error(void)
{
	cantalloc_clean();
	return (-1);
}

int	main(int ac, char **av)
{
	int			arg[5];
	t_program	program;
	t_philo		philo;

	if (!input_is_valid(ac, av, arg))
		return (error());
	if (!initialize_program(&program, &philo, arg))
		return (error());
	cantalloc_clean();
	return (0);
}
