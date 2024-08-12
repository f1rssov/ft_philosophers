/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pthread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcompreh <dcompreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:30:13 by dcompreh          #+#    #+#             */
/*   Updated: 2022/06/15 19:15:39 by dcompreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_in(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time);
}

void	feel_mutex(t_philos *philo, int i, t_arg *arg)
{
	if (i == 0)
	{
		philo->left_fork = &arg->forks[i];
		philo->right_fork = &arg->forks[arg->n_philo - 1];
	}
	else if (i == arg->n_philo - 1)
	{
		philo->left_fork = &arg->forks[i];
		philo->right_fork = &arg->forks[i - 1];
	}
	else if (i > 0 && (i != arg->n_philo - 1))
	{
		philo->left_fork = &arg->forks[i];
		philo->right_fork = &arg->forks[i - 1];
	}
	philo->sms = &arg->message;
	philo->ex = &arg->exx;
}

int	create_pthread(t_arg *arg)
{
	int			i;

	i = 0;
	arg->philo = malloc(sizeof (t_philos) * arg->n_philo);
	arg->start = time_in();
	while (i < arg->n_philo)
	{
		arg->philo[i].start = arg->start;
		arg->philo[i].id = i + 1;
		arg->philo[i].must_eat = arg->n_of_eat;
		arg->philo[i].time_eat = arg->time_to_eat;
		arg->philo[i].time_sleep = arg->time_to_sleep;
		feel_mutex(&arg->philo[i], i, arg);
		arg->philo[i].time = arg->start;
		arg->philo[i].time_to_die = arg->time_to_die;
		arg->philo[i].solo = arg->n_philo;
		pthread_create(&arg->philo[i].s1, NULL, &print, &arg->philo[i]);
		i++;
	}
	usleep(100);
	waiter_chec(arg);
	return (1);
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

// i = -1;
// while (++i < arg->n_philo)
	// 	pthread_join(arg->philo[i].s1, NULL);