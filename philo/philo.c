/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcompreh <dcompreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:03:19 by dcompreh          #+#    #+#             */
/*   Updated: 2022/05/31 17:33:11 by dcompreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg		arg;

	if (argc != 5 && argc != 6)
		return (printf("\e[1;91mERROR:not enough or too much arguments\033[0m\n"));
	if (init_all(argv, &arg))
		return (1);
	create_pthread(&arg);
	free(arg.forks);
	free(arg.eat_check);
	free(arg.philo);
	return (0);
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

// return (printf("\e[1;91mERROR:not enough or too much arguments\033[0m\n"));
// return (printf("\e[1;91mERROR: invalid arguments (n_eat)\033[0m\n"));
// return (printf("\e[1;91mERROR: invalid arguments\033[0m\n"));
// return (printf("\e[1;91mERROR: malloc error\033[0m\n"));
// return (printf("\e[1;91mERROR: malloc error\033[0m\n"));
// printf("%lld %d\e[0;35m is eating \033[0m\n", time_in() - philo->start,
// 			philo->id);
// printf("%lld %d\e[0;90m is sleeping \033[0m\n", time_in() - philo->start,
// 			philo->id);
// printf("%lld %d\e[0;32m is thinking \033[0m\n", time_in() - philo->start,
// 			philo->id);
// printf("%lld %d\e[0;36m has taken a fork \033[0m\n",
	// time_in() - philo->start, philo->id);