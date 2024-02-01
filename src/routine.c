/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:24:50 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/25 20:24:51 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	try_eat(t_philo *philo)
{
//	if (should_philosopher_stop(philo) == true)
//		return (FAILURE);
//	print_log(philo, THINK);
//	if (print_log_with_status_check(philo, THINK) == FAILURE)
//		return (FAILURE);
	if (try_take_forks(philo) == FAILURE)
		return (FAILURE);
//	pthread_mutex_lock(&philo->meal->mutex);
//	if (should_philosopher_stop(philo) == true)
//	{
//		release_forks(philo);
//		return (FAILURE);
//	}
//	print_log(philo, EAT);
	if (print_log_with_status_check(philo, EAT) == FAILURE)
		return (FAILURE);
	gettimeofday(&philo->meal->last_meal, NULL);
	pthread_mutex_lock(&philo->meal->mutex);
	if (philo->meal->number_of_meals_left != UNSPECIFIED)
		philo->meal->number_of_meals_left--;
	pthread_mutex_unlock(&philo->meal->mutex);
//	print_log(philo, "eating starts\n");
	ft_usleep(philo->sim_params.time_to_eat * US_PER_MS);
//	print_log(philo, "eating ends\n");
	release_forks(philo);
	return (SUCCESS);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	bool	should_continue;
	long	start_delay;

	philo = (t_philo *)arg;
	should_continue = (philo->meal->number_of_meals_left == UNSPECIFIED);
	print_log(philo, THINK);
	start_delay = (philo->id % 10) * 5; // Modulate by 10, multiply by 5ms for example
	ft_usleep(start_delay * US_PER_MS);
//	ft_usleep(philo->id * 5 * US_PER_MS);
	while (should_continue || philo->meal->number_of_meals_left > 0)
	{
		if (try_eat(philo) == FAILURE)
			return (NULL);
//		if (should_philosopher_stop(philo) == true)
//			return (NULL);
//		print_log(philo, SLEEP);
		if (print_log_with_status_check(philo, SLEEP) == FAILURE)
			return (NULL);
		ft_usleep(philo->sim_params.time_to_sleep * US_PER_MS);
		if (print_log_with_status_check(philo, THINK) == FAILURE)
			return (NULL);
	}
	return (NULL);
}
