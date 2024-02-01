/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:31:46 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/26 19:31:47 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, char *message)
{
	struct timeval	curr_time;
	long			elapsed_ms;

	gettimeofday(&curr_time, NULL);
	pthread_mutex_lock(&philo->sim_log->mutex);
	elapsed_ms = (curr_time.tv_sec - philo->sim_log->start_time.tv_sec) * MS_PER_SEC;
	elapsed_ms += (curr_time.tv_usec - philo->sim_log->start_time.tv_usec) / US_PER_MS;
	printf("%011ld %d %s", elapsed_ms, philo->id, message);
	pthread_mutex_unlock(&philo->sim_log->mutex);
}

int	print_log_with_status_check(t_philo *philo, char *message)
{
	struct timeval	curr_time;
	long			elapsed_ms;

	gettimeofday(&curr_time, NULL);
	elapsed_ms = (curr_time.tv_sec - philo->sim_log->start_time.tv_sec) * MS_PER_SEC;
	elapsed_ms += (curr_time.tv_usec - philo->sim_log->start_time.tv_usec) / US_PER_MS;
	pthread_mutex_lock(&philo->sim_status->mutex);
	if (philo->sim_status->should_stop == true)
	{
		pthread_mutex_unlock(&philo->sim_status->mutex);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->sim_status->mutex);
	pthread_mutex_lock(&philo->sim_log->mutex);
	printf("%011ld %d %s", elapsed_ms, philo->id, message);
	pthread_mutex_unlock(&philo->sim_log->mutex);
	return (SUCCESS);
}
