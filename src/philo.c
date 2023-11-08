/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:38:33 by eportela          #+#    #+#             */
/*   Updated: 2023/08/28 15:16:15 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_to_data(t_data *r_table, char **args, int argc)
{
	r_table->p_n = ft_positiveatoi(args[1]);
	r_table->time_to_die = ft_positiveatoi(args[2]);
	r_table->time_to_eat = ft_positiveatoi(args[3]);
	r_table->time_to_sleep = ft_positiveatoi(args[4]);
	ft_init_time(r_table);
	r_table->flag = 0;
	r_table->flag1 = 0;
	r_table->n_thread = r_table->p_n;
	if (pthread_mutex_init(&(r_table->end), NULL) != 0)
		return (error_handler(MUTEX_ERROR));
	if (pthread_mutex_init(&(r_table->lmeal), NULL) != 0)
		return (error_handler(MUTEX_ERROR));
	if (pthread_mutex_init(&(r_table->stillm), NULL) != 0)
		return (error_handler(MUTEX_ERROR));
	if (pthread_mutex_init(&(r_table->lock), NULL) != 0)
		return (error_handler(MUTEX_ERROR));
	if (argc == 5)
		r_table->number_of_must_meals = UNDEFINED;
	else
		r_table->number_of_must_meals = ft_positiveatoi(args[5]);
	return (SUCCESS);
}

int	alloc_philosophers(t_data *r_table)
{
	r_table->philos = malloc(sizeof(t_philo) * r_table->p_n);
	if (r_table->philos == NULL)
		return (error_handler(ALLOC_ERROR));
	r_table->forks = malloc(sizeof(t_fork) * r_table->p_n);
	if (r_table->forks == NULL)
		return (error_handler(ALLOC_ERROR));
	return (SUCCESS);
}

int	init_forks(t_data *r_table, int i)
{
	int	error;

	while (i < r_table->p_n)
	{
		error = pthread_mutex_init(&r_table->forks[i].fid, NULL);
		if (error != 0)
			return (error_handler(MUTEX_ERROR));
		r_table->forks[i].status = AVAILABLE;
		i++;
	}
	i = 0;
	if (r_table->p_n == 1)
		r_table->philos[0].left_fork = &r_table->forks[0];
	else
	{
		while (i < r_table->p_n - 1)
		{
			r_table->philos[i].left_fork = &r_table->forks[i];
			r_table->philos[i].right_fork = &r_table->forks[i + 1];
			i++;
		}
		r_table->philos[i].left_fork = &r_table->forks[i];
		r_table->philos[i].right_fork = &r_table->forks[0];
	}
	return (SUCCESS);
}

int	ft_spy(t_data *r_table)
{
	int	i;

	i = 0;
	while (r_table->flag == 0 && r_table->p_n != 1)
	{
		is_alive(&r_table->philos[i]);
		if (r_table->number_of_must_meals \
		!= UNDEFINED && checkforall(r_table) == TRUE)
			message_handler("", DONE, &r_table->philos[i]);
		i++;
		if (i == r_table->p_n - 1)
			i = 0;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	r_table;
	int		i;

	i = 0;
	if ((argc == 5 || argc == 6) && is_validinput(argv) == TRUE)
	{
		if (input_to_data(&r_table, argv, argc) == FAILED)
			return (FAILURE);
		if (alloc_philosophers(&r_table) == FAILED)
			return (FAILURE);
		if (init_forks(&r_table, 0) == FAILED)
			return (FAILURE);
		if (init_philosophers(&r_table, 0) == FAILED)
			return (FAILURE);
		ft_spy(&r_table);
		while (i < r_table.p_n)
			pthread_join(r_table.philos[i++].pid, NULL);
		clear_data(&r_table);
		return (SUCCESS);
	}
	return (error_handler(PARAM_ERROR));
}
