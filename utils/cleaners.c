/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:29:41 by eportela          #+#    #+#             */
/*   Updated: 2023/08/05 19:08:46 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	close_program(t_data *r_table)
{
	printf("%d\n", r_table->flag1);
}

void	clear_data(t_data *r_table)
{
	free(r_table->forks);
	free(r_table->philos);
}
