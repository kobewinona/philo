/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:02:14 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/31 14:02:16 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_dead(t_philo *philo)
{
	struct timeval	ct;
	long			et;

	gettimeofday(&ct, NULL);
	pthread_mutex_lock(&philo->meal->mutex);
	et = (ct.tv_sec - philo->meal->last_meal.tv_sec) * MS_PER_SEC;
	et += (ct.tv_usec - philo->meal->last_meal.tv_usec) / US_PER_MS;
	pthread_mutex_unlock(&philo->meal->mutex);
	if (et >= (philo->sim_params.time_to_die))
		return (true);
	return (false);
}

bool	has_philo_meals_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal->mutex);
	if (philo->meal->number_of_meals_left != UNSPECIFIED)
	{
		if (philo->meal->number_of_meals_left <= 0)
		{
			pthread_mutex_unlock(&philo->meal->mutex);
			return (true);
		}
	}
	pthread_mutex_unlock(&philo->meal->mutex);
	return (false);
}

bool	should_philo_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_status->mutex);
	if (philo->sim_status->should_stop == true)
	{
		pthread_mutex_unlock(&philo->sim_status->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->sim_status->mutex);
	return (false);
}
