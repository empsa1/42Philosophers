/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:13:54 by eportela          #+#    #+#             */
/*   Updated: 2023/08/05 20:55:31 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_validinput(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (ft_positiveatoi(args[i++]) == FAILED)
			return (FAILED);
	}
	return (TRUE);
}

int	is_validint(long long n)
{
	if (n > INT_MAX || n < 0)
		return (error_handler("input wasnt valid"));
	return (n);
}

void	message_handler(char *error_msg, int type, t_philo *philo)
{
	int		flag;
	long	time;

	pthread_mutex_lock(&philo->r_table->end);
	flag = philo->r_table->flag;
	time = ft_get_time(philo->r_table);
	if (type == DIED)
		printf("%li %d %s\n", time, philo->id, error_msg);
	else if (type == DONE)
	{
		pthread_mutex_unlock(&philo->r_table->end);
		return ;
	}
	else if (flag != 0)
	{
		pthread_mutex_unlock(&philo->r_table->end);
		return ;
	}
	else if (type == EATING || type == THINKING || \
	type == SLEEPING || type == FORKING)
		printf("%li %d %s\n", time, philo->id, error_msg);
	else
		printf("%s\n", error_msg);
	pthread_mutex_unlock(&philo->r_table->end);
}

int	error_handler(char *str)
{
	printf("%s\n", str);
	return (FAILED);
}
