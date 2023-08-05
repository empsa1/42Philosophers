/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:18:01 by eportela          #+#    #+#             */
/*   Updated: 2023/08/05 19:46:21 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
		return (error_handler(MUTEX_ERROR));
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ft_init_time(t_data *r_table)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	r_table->time_sec = current_time.tv_sec;
	r_table->time_usec = current_time.tv_usec;
}

long	ft_get_time(t_data *r_table)
{
	struct timeval	current_time;
	long int		exec_time;

	gettimeofday(&current_time, NULL);
	exec_time = ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) \
		- (r_table->time_sec * 1000 + r_table->time_usec / 1000));
	return (exec_time);
}

void	ft_sleep(int num)
{
	unsigned long	time_end;

	time_end = get_time() + num;
	while (get_time() < time_end)
		usleep(10);
}
