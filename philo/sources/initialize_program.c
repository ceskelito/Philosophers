#include "philo.h"

static bool	initialize_philo(t_philo *philo)
{
	philo->r_fork = cantalloc(sizeof(pthread_mutex_t));
	if (!philo->r_fork)
		return (false);
	philo->l_fork = cantalloc(sizeof(pthread_mutex_t));
	if (!philo->l_fork)
		return (false);
	philo->write_lock = cantalloc(sizeof(pthread_mutex_t));
	if (!philo->write_lock)
		return (false);
	philo->dead_lock = cantalloc(sizeof(pthread_mutex_t));
	if (!philo->dead_lock)
		return (false);
	philo->meal_lock = cantalloc(sizeof(pthread_mutex_t));
	if (!philo->meal_lock)
		return (false);
	pthread_mutex_init(philo->r_fork, NULL);
	pthread_mutex_init(philo->l_fork, NULL);
	pthread_mutex_init(philo->write_lock, NULL);
	pthread_mutex_init(philo->dead_lock, NULL);
	pthread_mutex_init(philo->meal_lock, NULL);
	return (true);
}

bool initialize_program(t_program *program, t_philo *philo, int *arg)
{
	program->philos = cantalloc(sizeof(t_philo *));
	if (!program->philos)
		return (false);
	program->philos = philo;
	program->num_of_philos = arg[num_of_philos];
	program->time_to_die = arg[time_to_die];
	program->time_to_eat = arg[time_to_eat];
	program->time_to_sleep = arg[time_to_sleep];
	program->meals_to_eat = arg[meals_to_eat];
	return (initialize_philo(philo));
}
