/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:33:41 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/11/02 16:53:37 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		ft_counter(t_state *state)
{
	int		amount;
	int		i;


	i = 0;
	amount = 0;
	while (amount < state->must_eat_count)
	{
		while (i < state->amount)
			pthread_mutex_lock(&state->philo[i++].eat_m);
		amount++;
	}
	ft_error("HAN COMIDO");
	return (0);
}
