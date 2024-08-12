/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcompreh <dcompreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:44:00 by dcompreh          #+#    #+#             */
/*   Updated: 2022/05/31 18:10:11 by dcompreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philos
{
	pthread_t		s1;
	int				id;
	int				must_eat;
	int				time_eat;
	int				time_sleep;
	int				solo;
	int				time_to_die;
	int				s_kill;
	int				s_dead;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*sms;
	pthread_mutex_t	*ex;
	long long		start;
	int				s_eated;
	int				s_exit;
	long long		time;
}	t_philos;

typedef struct s_waiter
{
	int			num_eat;
	int			end;
}	t_waiter;

typedef struct s_arg
{
	long long		start;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_eat;
	int				*eat_check;
	t_philos		*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	exxit;
	pthread_mutex_t	exx;
}	t_arg;

int			ft_atoi(const char *str);
void		*print(void *b);
int			create_pthread(t_arg *arg);
int			init_all(char **argv, t_arg *arg);
long long	time_in(void);
void		unlock_forks(t_philos *philo);
void		lock_forks(t_philos *philo);
void		waiter_chec(t_arg *arg);
int			proverka(t_philos *philo);
void		f_sleep(t_philos *philo, int i);
int			fork_for_one(t_philos *philo);
void		take_forks(t_philos *philo);
int			i_ate(t_philos *philo);
void		need_to_print(t_philos *philo, int i);

#endif

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