/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:33:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/01 15:33:17 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	get_curr_time_us(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return (ct.tv_sec * US_PER_SEC + ct.tv_usec);
}

//void	ft_usleep(long long usec)
//{
//	long long	start;
//
//	start = get_curr_time_us();
//	while (get_curr_time_us() - start < usec)
//		usleep(1000);
//}

void	ft_usleep(long long usec)
{
	long long	start;
	long long	end;

	start = get_curr_time_us();
	end = start + usec;
	while (get_curr_time_us() < end)
	{
		if ((end - get_curr_time_us()) > 5000)
			usleep(4000);
		else
		{
			while (get_curr_time_us() < end)
				usleep(1000);
			break ;
		}
	}
}
