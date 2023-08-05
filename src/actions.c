/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:38:22 by eportela          #+#    #+#             */
/*   Updated: 2023/08/05 20:26:19 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickl_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fid);
	message_handler(PICKL_FORK, FORKING, philo);
	philo->left_fork->status = BUSY;
}

void	pickr_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fid);
	message_handler(PICKR_FORK, FORKING, philo);
	philo->right_fork->status = BUSY;
}

void	start_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->stat);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->stat);
	if (philo->id % 2 == 1)
	{
		pickl_forks(philo);
		pickr_forks(philo);
	}
	else
	{
		pickr_forks(philo);
		pickl_forks(philo);
	}
	philo->status = EATING;
	message_handler(EAT, EATING, philo);
	pthread_mutex_lock(&philo->r_table->lmeal);
	philo->last_meal = ft_get_time(philo->r_table) + philo->time_to_die;
	pthread_mutex_unlock(&philo->r_table->lmeal);
	ft_sleep(philo->time_to_eat);
	mealy(philo);
	drop_forks(philo);
}

void	drop_forks(t_philo *philo)
{
	philo->left_fork->status = AVAILABLE;
	if (philo->id % 2 == 1)
	{
		philo->right_fork->status = AVAILABLE;
		pthread_mutex_unlock(&philo->right_fork->fid);
		philo->left_fork->status = AVAILABLE;
		pthread_mutex_unlock(&philo->left_fork->fid);
	}
	else
	{
		philo->left_fork->status = AVAILABLE;
		pthread_mutex_unlock(&philo->left_fork->fid);
		philo->right_fork->status = AVAILABLE;
		pthread_mutex_unlock(&philo->right_fork->fid);
	}
	start_sleeping(philo);
}

void	start_sleeping(t_philo *philo)
{
	philo->status = SLEEPING;
	message_handler(SLEEP, SLEEPING, philo);
	ft_sleep(philo->time_to_sleep);
	start_thinking(philo);
}
