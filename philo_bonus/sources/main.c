/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:15:16 by rceschel          #+#    #+#             */
/*   Updated: 2025/09/15 18:41:11 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_philo *philo)
{
	printf("PID: %d\nPhilo: %d\n------\n", getpid(), philo->id);
}

void	*philos_birth(void *param)
{
	t_program	*program;
	t_philo		philo;
	int			n_philos;
	int			i;
	program = (t_program *) param;
	n_philos = program->rules[e_num_of_philos];
	//
	// Processes creation
	//
	// Due the fact the main program should not act as a philo
	// i think there's the need to create a thread in wich
	// do the fork() system call
	//
	i = 0;
	while (i < n_philos)
	{
		if (program->philos_pid[i] > 0)
		{
			program->philos_pid[i] = fork();
		}
		if (program->philos_pid[i] < 0)
		{
			sleep(500);
			// Free resources and exit
		}
		if (program->philos_pid[i] == 0)
		{
			philo.id = i + 1;
			philo.forks = sem_open("/forks", O_CREAT | O_EXCL, 0666, n_philos);
			//philo.sem_write = sem_open("/write", O_CREAT | O_EXCL, 0666, 1);
			
			// if !forks || sem_write : exit
	
			print_info(&philo);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_program	program;
	t_philo		philos_template;

	--argc;
	++argv;
	if (!input_is_valid(argc, argv, program.rules))
		return (-1);
	initialize_program(&program, &philos_template);
	initialize_philos_template(&philos_template, program.rules);
	philos_birth(&program);
	waitpid(-1, NULL, 0);
	//sem_wait(&program.sem_write);
	int i = 0;
	while (i < program.rules[e_num_of_philos])
	{
		kill(program.philos_pid[i], SIGTERM);
		i++;
	}
	//sem_post(&program.sem_write);
	return (0);

}
