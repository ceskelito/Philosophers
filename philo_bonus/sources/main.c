/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:15:16 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/16 16:46:30 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_and_exit(t_program *program, int exit_code)
{
	int	i;

	i = 0;
	while (i < program->rules[e_num_of_philos])
	{
		if (program->philos_pid[i] > 0)
			kill(program->philos_pid[i], SIGTERM);
		i++;
	}
	sem_unlink("/write");
	sem_unlink("/forks");
	sem_unlink("/eat");
	if (program->write_sem)
		sem_close(program->write_sem);
	if (program->eat_sem)
		sem_close(program->eat_sem);
	free(program->philos_pid);
	exit(exit_code);
}

static void	philos_birth(t_program *program)
{
	t_philo	philo;
	int		n_philos;
	int		i;

	n_philos = program->rules[e_num_of_philos];
	i = 0;
	while (i < n_philos)
	{
		program->philos_pid[i] = fork();
		if (program->philos_pid[i] < 0)
		{
			ft_write(2, "Fork failed\n");
			cleanup_and_exit(program, 1);
		}
		if (program->philos_pid[i] == 0)
		{
			if (!initialize_philo(&philo, program->rules, i + 1))
				exit(1);
			routine(&philo);
			exit(0);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (!input_is_valid(--argc, ++argv, program.rules))
		return (-1);
	if (!initialize_program(&program))
		return (printf("Program initialization failed\n"), 1);
	philos_birth(&program);
	if (program.rules[e_meals_to_eat] > -1)
	{
		pthread_create(&program.meal_monitor, NULL, have_philos_ate, &program);
		pthread_detach(program.meal_monitor);
	}
	waitpid(-1, NULL, 0);
	cleanup_and_exit(&program, 0);
}
