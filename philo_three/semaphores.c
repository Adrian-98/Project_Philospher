/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:22:05 by ncolomer          #+#    #+#             */
/*   Updated: 2020/11/05 21:06:21 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

sem_t	*ft_sem_open(char const *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char	*make_semaphore_name(char const *base, char *buffer, int position)
{
	int	i;

	i = ft_strcpy(buffer, base);
	while (position > 0)
	{
		buffer[i++] = (position % 10) + '0';
		position /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}

int			init_semaphores(t_state *state)
{
	if ((state->forks_m = ft_sem_open(SEMAPHORE_FORK, state->amount)) < 0
		|| (state->write_m = ft_sem_open(SEMAPHORE_WRITE, 1)) < 0
		|| (state->somebody_dead_m = ft_sem_open(SEMAPHORE_DEAD, 0)) < 0
		|| (state->dead_write_m = ft_sem_open("SEMAPHORE_DEADW", 1)) < 0)
		return (1);
	return (0);
}
