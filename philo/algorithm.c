/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcompreh <dcompreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:46:23 by dcompreh          #+#    #+#             */
/*   Updated: 2022/06/15 18:11:32 by dcompreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	proverka(t_philos *philo)
{
	pthread_mutex_lock(philo->ex);
	if (philo->s_exit == 1)
	{
		pthread_mutex_unlock(philo->ex);
		return (1);
	}
	if (philo->s_dead == 1)
	{
		pthread_mutex_unlock(philo->ex);
		return (2);
	}
	pthread_mutex_unlock(philo->ex);
	return (0);
}

void	need_to_print(t_philos *philo, int i)
{
	if (proverka(philo))
		return ;
	if (i == 1)
		printf("%lld %d is eating\n", time_in() - philo->start,
			philo->id);
	if (proverka(philo))
		return ;
	if (i == 0)
		printf("%lld %d is sleeping\n", time_in() - philo->start,
			philo->id);
	if (proverka(philo))
		return ;
	if (i == 2)
		printf("%lld %d is thinking\n", time_in() - philo->start,
			philo->id);
}

int	print_what_do(t_philos *philo, int i)
{
	if (proverka(philo))
	{
		unlock_forks(philo);
		return (proverka(philo));
	}
	i_ate(philo);
	pthread_mutex_lock(philo->ex);
	if (i == 0)
		philo->must_eat--;
	pthread_mutex_unlock(philo->ex);
	if (proverka(philo))
	{
		unlock_forks(philo);
		return (proverka(philo));
	}
	pthread_mutex_lock(philo->sms);
	need_to_print(philo, 0);
	pthread_mutex_unlock(philo->sms);
	unlock_forks(philo);
	f_sleep(philo, 2);
	pthread_mutex_lock(philo->sms);
	need_to_print(philo, 2);
	pthread_mutex_unlock(philo->sms);
	return (0);
}

int	alg_for_one(t_philos *philo)
{
	if (fork_for_one(philo))
		return (1);
	return (0);
}

void	*print(void *buf)
{
	t_philos	*philo;
	int			i;

	i = 0;
	philo = (t_philos *)buf;
	pthread_mutex_lock(philo->ex);
	if (philo->must_eat == -1)
	{
		philo->must_eat = 1;
		i = 1;
	}
	pthread_mutex_unlock(philo->ex);
	while (1)
	{
		if (proverka(philo))
			return (0);
		if (philo->solo == 1 && alg_for_one(philo))
			return (0);
		lock_forks(philo);
		if (print_what_do(philo, i) == 2)
			return (0);
		if (proverka(philo))
			return (0);
	}
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
