/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:23:28 by eportela          #+#    #+#             */
/*   Updated: 2023/08/05 21:23:17 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_easy(t_data *r_table, int i)
{
	while (i < r_table->p_n)
	{
		r_table->philos[i].r_table = r_table;
		r_table->philos[i].flagg = 0;
		r_table->philos[i].id = i + 1;
		r_table->philos[i].time_to_die = r_table->time_to_die;
		r_table->philos[i].time_to_eat = r_table->time_to_eat;
		r_table->philos[i].time_to_sleep = r_table->time_to_sleep;
		i++;
	}
	return (SUCCESS);
}

int	init_philosophers(t_data *r_table, int i)
{
	init_philo_easy(r_table, 0);
	while (i < r_table->p_n)
	{
		if (r_table->number_of_must_meals == UNDEFINED)
			r_table->philos[i].n_meals = -1;
		else
			r_table->philos[i].n_meals = 0;
		r_table->philos[i].last_meal = ft_get_time(r_table) \
		+ r_table->time_to_die;
		if (pthread_mutex_init(&(r_table->philos[i].stat), NULL) != 0)
			return (error_handler(MUTEX_ERROR));
		if (pthread_mutex_init(&(r_table->philos[i].alive), NULL) != 0)
			return (error_handler(MUTEX_ERROR));
		if (pthread_mutex_init(&(r_table->philos[i].main1), NULL) != 0)
			return (error_handler(MUTEX_ERROR));
		if (r_table->p_n == 1)
			return (eating_1p(&r_table->philos[0]));
		else
			if (pthread_create(&r_table->philos[i].pid, NULL, \
			(void *)p_handler, &r_table->philos[i]) != 0)
				return (error_handler(THREAD_ERROR));
		i++;
	}
	return (SUCCESS);
}

void	single_handler(t_philo *philo)
{
	long	time;

	message_handler(PICKL_FORK, FORKING, philo);
	ft_sleep(philo->r_table->time_to_die);
	time = ft_get_time(philo->r_table);
	printf("%li %d %s\n", time, philo->id, DEAD);
	return ;
}

void	p_handler(t_philo *philo)
{
	int	tester;
	int	c;

	c = 0;
	if (philo->id % 2 != 1)
		ft_sleep(philo->time_to_eat);
	if (c == 0)
	{
		c = 1;
		pthread_mutex_lock(&philo->main1);
		philo->timer = ft_get_time(philo->r_table);
		pthread_mutex_unlock(&philo->main1);
	}
	tester = 0;
	while (tester == 0)
	{
		start_eating(philo);
		pthread_mutex_lock(&philo->r_table->end);
		tester = philo->r_table->flag;
		pthread_mutex_unlock(&philo->r_table->end);
	}
	return ;
}
