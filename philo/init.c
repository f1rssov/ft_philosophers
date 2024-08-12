/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcompreh <dcompreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:14:57 by dcompreh          #+#    #+#             */
/*   Updated: 2022/05/30 17:47:08 by dcompreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_arg *arg)
{
	int		i;

	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->n_philo - 1);
	if (!(arg->forks))
		return (printf("\e[1;91mERROR: malloc error\033[0m\n"));
	arg->eat_check = malloc(sizeof(int) * arg->n_philo - 1);
	if (!(arg->eat_check))
		return (printf("\e[1;91mERROR: malloc error\033[0m\n"));
	i = -1;
	while (++i < arg->n_philo)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			return (1);
	}
	i = -1;
	while (++i < arg->n_philo)
		arg->eat_check[i] = arg->n_of_eat;
	if (pthread_mutex_init(&(arg->message), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->exx), NULL))
		return (1);
	return (0);
}	

int	init_all(char **argv, t_arg *arg)
{
	arg->n_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (arg->n_philo < 1 || arg->time_to_eat <= 0 || arg->time_to_die < 0
		|| arg->time_to_sleep <= 0)
		return (printf("\e[1;91mERROR: invalid arguments\033[0m\n"));
	if (argv[5])
	{
		arg->n_of_eat = ft_atoi(argv[5]);
		if (arg->n_of_eat <= 0)
			return (printf("\e[1;91mERROR: invalid arguments (n_eat)\033[0m\n"));
	}
	else
		arg->n_of_eat = -1;
	return (init_mutex(arg));
}

// pthread_mutex_t mutex; - создание переменной мьютекс
// pthread_mutex_init(&mutex, NULL); - инициализация мьютекс
// pthread_mutex_destroy(&mutex); - уничтожение мьютекс
// pthread_mutex_lock(&mutex); - блокировка мьютексом
// pthread_mutex_unlock(&mutex); - разблокировка мьютексом
// pthread_create(&s1, NULL, print, (void *)b); - создаёт параллельный поток
// pthread_detach(s1); - не ждёт завершения потока s1 и идёт дальше
// pthread_join(s1, NULL); - ждёт завершения потока s1 после чего идёт дальше
// usleep(100000); - команда говорит ждать в течении N времени (в микросекудах)
// void *print(void *param)

// waiter->end = waiter->current_time.tv_usec 
// + (waiter->current_time.tv_sec * 1000000);
// time = (waiter->end - waiter->start) / 1000;