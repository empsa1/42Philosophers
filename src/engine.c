/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:38:42 by eportela          #+#    #+#             */
/*   Updated: 2023/08/05 21:15:32 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->main1);
	time = ft_get_time(philo->r_table);
	pthread_mutex_unlock(&philo->main1);
	pthread_mutex_lock(&philo->alive);
	pthread_mutex_lock(&philo->r_table->lmeal);
	if (time > philo->last_meal)
	{
		pthread_mutex_unlock(&philo->alive);
		pthread_mutex_lock(&philo->r_table->end);
		philo->r_table->flag = 1;
		pthread_mutex_unlock(&philo->r_table->end);
		message_handler(DEAD, DIED, philo);
	}
	else
		pthread_mutex_unlock(&philo->alive);
	pthread_mutex_unlock(&philo->r_table->lmeal);
	return (TRUE);
}

int	checkforall(t_data *r_table)
{
	int	i;

	i = 0;
	while (i < r_table->p_n - 1)
	{
		pthread_mutex_lock(&r_table->philos[i].stat);
		if (r_table->philos[i].flagg == 0)
		{
			pthread_mutex_unlock(&r_table->philos[i].stat);
			return (FALSE);
		}
		pthread_mutex_unlock(&r_table->philos[i].stat);
		i++;
	}
	pthread_mutex_lock(&r_table->end);
	r_table->flag = 2;
	pthread_mutex_unlock(&r_table->end);
	return (TRUE);
}

void	mealy(t_philo *philo)
{
	pthread_mutex_lock(&philo->stat);
	if (philo->flagg == 0 && \
	philo->n_meals >= philo->r_table->number_of_must_meals)
		philo->flagg = 1;
	pthread_mutex_unlock(&philo->stat);
}

int	eating_1p(t_philo *philo)
{
	if (pthread_create(&philo->pid, NULL, (void *)single_handler, \
		&philo[0]) != 0)
		return (error_handler(THREAD_ERROR));
	return (SUCCESS);
}

void	start_thinking(t_philo *philo)
{
	philo->status = THINKING;
	message_handler(THINK, THINKING, philo);
}
