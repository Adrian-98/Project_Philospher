/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:44:49 by adrian            #+#    #+#             */
/*   Updated: 2020/11/05 18:17:18 by amunoz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define EAT 	0
# define SLEEP 	1
# define FORK 	2
# define THINK	3
# define DIED 	4
# define OVER 	5

# define SEMAPHORE_FORK		"pSemaphoreFork"
# define SEMAPHORE_WRITE	"pSemaphoreWrite"
# define SEMAPHORE_DEAD		"pSemaphoreDead"
# define SEMAPHORE_PHILO	"pSemaphorePhilo"
# define SEMAPHORE_PHILOEAT	"pSemaphorePhiloEat"


typedef struct s_philo
{
	int				position;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				lfork;
	int				rfork;
	int				eat_count;
	struct s_state	*state;
	sem_t			*mutex;
	sem_t			*eat_count_m;
}				t_philo;

typedef struct s_state
{
	int				amount;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				must_eat_count;
	int				eat_counter;

	uint64_t		start;

	struct s_philo	*philo;
	sem_t			*forks_m;
	sem_t			*write_m;
	sem_t			*somebody_dead_m;

}				t_state;



int						ft_strlen(char *str);
int						ft_atoi(char const *str);
void					ft_putnbr_fd(uint64_t n, int fd);
uint64_t				get_time(void);
int						ft_error(char *str);
int						message(t_philo *philo, int type);
int						init_semaphores(t_state *state);
void					*ft_body(void *philo_v);
void					ft_monitor(t_philo *philo);
int						ft_counter(t_state *state);
void					ft_eat_counter(t_state *state);
char					*make_semaphore_name(char const *base, char *buffer, int position);
sem_t					*ft_sem_open(char const *name, int value);
int						ft_strcpy(char *dst, const char *src);



#endif