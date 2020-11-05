/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:44:39 by adrian            #+#    #+#             */
/*   Updated: 2020/11/05 17:14:36 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_philos(t_state *state)
{
	int		i;
	char	semaphore[250];

	i = 0;
	while (i < state->amount)
	{
		state->philo[i].is_eating = 0;
		state->philo[i].position = i;
		state->philo[i].lfork = i;
		state->philo[i].rfork = (i + 1) % state->amount;
		state->philo[i].eat_count = 0;
		state->philo[i].state = state;
		make_semaphore_name(SEMAPHORE_PHILO, (char*)semaphore, i);
		if ((state->philo[i].mutex = ft_sem_open(semaphore, 1)) < 0)
			return (1);
		make_semaphore_name(SEMAPHORE_PHILOEAT, (char*)semaphore, i);
		if ((state->philo[i].eat_count_m = ft_sem_open(semaphore, 0)) < 0)
			return (1);
		i++;
	}
	init_semaphores(state);
	return (0);
}

static	int		fill_struct(t_state *state, int argc, char **argv)
{
	t_philo *philo;

	state->amount = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->must_eat_count = ft_atoi(argv[5]);
	else
		state->must_eat_count = 0;
	if (!(philo = malloc(sizeof(t_philo))))
		return(ft_error("Error: malloc failed\n"));
	if (state->amount < 2 || state->amount > 200 || state->time_to_die < 60
		|| state->time_to_eat < 60 || state->time_to_sleep < 60
		|| state->must_eat_count < 0)
		return (0);
	state->eat_counter = 0;
	if (!(state->philo =
		(t_philo*)malloc(sizeof(*(state->philo)) * state->amount)))
		return (0);
	if (init_philos(state) == 1)
		return (0);
	return (1);
}

int		start_threads(t_state *state)
{
	pthread_t	id[state->amount];
	int i;

	state->start = get_time();
	// if (state->must_eat_count > 0)
	// 	ft_eat_counter(state);
	i = -1;
	while (++i < state->amount)
	{
		state->philo[i].last_eat = get_time();
		if(pthread_create(&id[i], NULL, (void *)&ft_body, &state->philo[i]) != 0)
			return (ft_error("Error: creating threads\n"));
		usleep(100);
	}
	return 0;
}

int main(int argc, char **argv)
{
	t_state *state;
	
	if (!(state = malloc(sizeof(t_state))))
		return(ft_error("Error: malloc failed\n"));
	if (argc < 5 || argc > 6)
		return(ft_error("ERROR :wrong number of arguments \n"));
	if (fill_struct(state, argc, argv) == 0)
			return(ft_error("Error : wrong parameters or malloc fail\n"));
	start_threads(state);
	sem_wait(state->somebody_dead_m);
	return (0);
}