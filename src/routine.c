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
	if (try_take_forks(philo) == FAILURE)
		return (FAILURE);
	if (should_philo_stop(philo) == true)
	{
		release_forks(philo);
		return (FAILURE);
	}
	print_log(philo, EAT);
	pthread_mutex_lock(&philo->meal->mutex);
	gettimeofday(&philo->meal->last_meal, NULL);
	if (philo->meal->number_of_meals_left != UNSPECIFIED)
		philo->meal->number_of_meals_left--;
	pthread_mutex_unlock(&philo->meal->mutex);
	ft_usleep(philo->sim_params.time_to_eat * US_PER_MS);
	release_forks(philo);
	return (SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	bool	should_go_on_forever;

	philo = (t_philo *)arg;
	should_go_on_forever = (philo->meal->number_of_meals_left == UNSPECIFIED);
	print_log(philo, THINK);
	if (philo->sim_start_delay > 0)
		ft_usleep(philo->sim_start_delay * US_PER_MS);
	while (should_go_on_forever || philo->meal->number_of_meals_left > 0)
	{
		if (try_eat(philo) == FAILURE)
			return (NULL);
		if (should_philo_stop(philo) == true)
			return (NULL);
		print_log(philo, SLEEP);
		ft_usleep(philo->sim_params.time_to_sleep * US_PER_MS);
		if (should_philo_stop(philo) == true)
			return (NULL);
		print_log(philo, THINK);
	}
	return (NULL);
}
