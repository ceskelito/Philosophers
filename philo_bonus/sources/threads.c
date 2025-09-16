/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:03 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/16 16:00:32 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Monitor thread to check if all philosophers have eaten required meals
void	*have_philos_ate(void *param)
{
	t_program	*program;
	int			i;

	program = param;
	i = 0;
	while (i < program->rules[e_num_of_philos])
	{
		sem_wait(program->eat_sem);
		i++;
	}
	i = 0;
	sem_wait(program->write_sem);
	while (i < program->rules[e_num_of_philos])
	{
		if (program->philos_pid[i] > 0)
			kill(program->philos_pid[i], SIGTERM);
		i++;
	}
	sem_post(program->write_sem);
	return (NULL);
}
