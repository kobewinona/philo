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

// ct = current time, et = elapsed time
void	print_log(t_philo *philo, char *message)
{
	struct timeval	ct;
	long			et;

	gettimeofday(&ct, NULL);
	pthread_mutex_lock(&philo->sim_log->mutex);
	et = (ct.tv_sec - philo->sim_log->start_time.tv_sec) * MS_PER_SEC;
	et += (ct.tv_usec - philo->sim_log->start_time.tv_usec) / US_PER_MS;
	printf("%011ld %d %s", et, philo->id, message);
	pthread_mutex_unlock(&philo->sim_log->mutex);
}

int	print_log_with_status_check(t_philo *philo, char *message)
{
	struct timeval	ct;
	long			et;

	gettimeofday(&ct, NULL);
	et = (ct.tv_sec - philo->sim_log->start_time.tv_sec) * MS_PER_SEC;
	et += (ct.tv_usec - philo->sim_log->start_time.tv_usec) / US_PER_MS;
	pthread_mutex_lock(&philo->sim_status->mutex);
	if (philo->sim_status->should_stop == true)
	{
		pthread_mutex_unlock(&philo->sim_status->mutex);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->sim_status->mutex);
	pthread_mutex_lock(&philo->sim_log->mutex);
	printf("%011ld %d %s", et, philo->id, message);
	pthread_mutex_unlock(&philo->sim_log->mutex);
	return (SUCCESS);
}
