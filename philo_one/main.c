/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:26:47 by amunoz-p          #+#    #+#             */
/*   Updated: 2020/10/28 19:49:07 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		init_mutex(t_state *state)
{
	int i = 0;
	
	pthread_mutex_init(&state->write_m, NULL);
	pthread_mutex_init(&state->somebody_dead_m, NULL);
	pthread_mutex_lock(&state->somebody_dead_m);
	if (!(state->forks_m =
		(pthread_mutex_t*)malloc(sizeof(*(state->forks_m)) * state->amount)))
		return (1);
	i = 0;
	while (i < state->amount)
		pthread_mutex_init(&state->forks_m[i++], NULL);
	return (0);
}

void		init_philos(t_state *state)
{
	int i;

	i = 0;
	while (i < state->amount)
	{
		state->philo[i].position = i;
		state->philo[i].is_eating = 0;
		state->philo[i].lfork = i;
		state->philo[i].rfork = (i + 1) % state->amount;
		state->philo[i].eat_count = 0;
		pthread_mutex_init(&state->philo[i].mutex, NULL);
		pthread_mutex_init(&state->philo[i].eat_m, NULL);
		pthread_mutex_lock(&state->philo[i].eat_m);
		i++;
	}
}

int			fill_struct(t_state *state, int argc, char **argv)
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
	if (state->amount < 2 || state->amount > 200 || state->time_to_die < 60
		|| state->time_to_eat < 60 || state->time_to_sleep < 60
		|| state->must_eat_count < 0)
		return (0);	
	if (!(state->philo = malloc(sizeof(t_philo) * state->amount)))
		return (0);
	init_philos(state);
	return (1);
}

int		start_threads(t_state *state)
{
	int i;
	pthread_t	id[state->amount];
	
	state->start = get_time();
	i = 0;
	while (i < state->amount)
	{
		pthread_create(&id[i], NULL, (void *)ft_body, &state->philo[i]);
		i++;
		usleep(100);
	}
}

int			main(int argc, char **argv)
{
	t_state	state;

	if (argc < 5 || argc > 6)
		return(ft_error("ERROR :wrong number of arguments \n"));
	if (fill_struct(&state, argc, argv) == 0)
			return(ft_error("Error : wrong parameters or malloc fail\n"));
	init_mutex(&state);
	start_threads(&state);
	return (0);
}