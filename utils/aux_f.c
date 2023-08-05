/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:12:25 by eportela          #+#    #+#             */
/*   Updated: 2023/08/05 20:58:34 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	aux_signal(char c)
{
	if (c == '-')
		return (-1);
	if (c == '+')
		return (1);
	return (0);
}

int	ft_positiveatoi(char *str)
{
	long long	result;
	int			signal;

	signal = 1;
	result = 0;
	if (is_validint(*str) == FALSE)
		return (FAILED);
	if (aux_signal(*str) != 0)
		signal = aux_signal(*str++);
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (FAILED);
		result = result * 10 + (*str++ - '0');
	}
	return (is_validint(result * signal));
}
