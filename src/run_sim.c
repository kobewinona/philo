/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:41:59 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/26 12:42:00 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_and_start_threads(t_sim **sim)
{
	long	start_delay;
	int		i;

	(*sim)->threads = (pthread_t *)malloc(
			(*sim)->params.number_of_philos * sizeof(pthread_t));
	if (!(*sim)->threads)
		return (ERROR);
	(*sim)->log.start_time = get_timestamp();
	start_delay = 0;
	i = 0;
	while (i < (*sim)->params.number_of_philos)
	{
		(*sim)->philos[i].meal->last_meal = (*sim)->log.start_time;
		if ((*sim)->params.number_of_philos % 2 != 0)
			start_delay = (i % 10) * 5;
		(*sim)->philos[i].sim_start_delay = start_delay;
		if (pthread_create(&(*sim)->threads[i], NULL,
				philo_routine, &(*sim)->philos[i]) != SUCCESS)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static void	join_threads(t_sim **sim)
{
	int	i;

	i = 0;
	while (i < (*sim)->params.number_of_philos)
	{
		pthread_join((*sim)->threads[i], NULL);
		i++;
	}
}

static void	update_sim_status(t_sim **sim)
{
	int	philos_finished_their_meals;
	int	i;

	philos_finished_their_meals = 0;
	i = 0;
	while (i < (*sim)->params.number_of_philos)
	{
		if (has_philo_meals_left(&(*sim)->philos[i]) == true)
			philos_finished_their_meals++;
		if (philos_finished_their_meals == (*sim)->params.number_of_philos)
		{
			(*sim)->status.stop_event = NO_MEALS_LEFT;
			return ;
		}
		if (is_philo_dead(&(*sim)->philos[i]))
		{
			(*sim)->status.stop_event = PHILO_DIED;
			(*sim)->status.philo_id = i;
			return ;
		}
		i++;
	}
}

void	run_sim(t_sim **sim)
{
	if (init_and_start_threads(&(*sim)) == ERROR)
		return ;
	while (1)
	{
		update_sim_status(&(*sim));
		if ((*sim)->status.stop_event != NO_STOP_EVENT)
		{
			if ((*sim)->status.stop_event == PHILO_DIED)
				print_log(&(*sim)->philos[(*sim)->status.philo_id], DIE);
			pthread_mutex_lock(&(*sim)->status.mutex);
			(*sim)->status.should_stop = true;
			pthread_mutex_unlock(&(*sim)->status.mutex);
			if ((*sim)->params.number_of_philos == 1)
				pthread_mutex_unlock(&(*sim)->forks[0].mutex);
			join_threads(&(*sim));
			return ;
		}
		smart_usleep(MAX_MS_TO_ANNOUNCE_DEATH);
	}
}
