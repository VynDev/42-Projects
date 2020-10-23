/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:48:24 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:37:40 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_CLIENT_H
# define FT_IRC_CLIENT_H
# include "ft_irc.h"

# define ENV_MAXMEMSLOTS 5

typedef struct			s_sock
{
	char 				type; // <== ici
	int					fd;
	t_packet			packet;
	t_cbuffer			*cbuf;
	t_cbuffer			*w_cbuf;
}						t_sock;

typedef struct			s_env
{
	t_sock				*sock;
	fd_set				fdset_read;
	fd_set				fdset_write;
	int					fdset_max;
	void				**memslots;
	int					log;
	int					debug;
}						t_env;

void					c_exit(int res, int err, char *str);
void					cv_exit(void *res, void *err, char *str);

void					init_env(t_env *e);
void					init_server(t_env *e);
void					main_loop(t_env *e);
void					init_fdset(t_env *e);
void					read_fds(t_env *e);
void					clear_sock(t_env *e);
void					get_message(t_env *e, int fdsender, char *buffer, int len);
void					free_env(t_env *e);

int						get_args(t_env *e, char *str, int nb);
void					print_memslots(t_env *e, int nb);

t_cbuffer				*cbuf_create(int size);
int						cbuf_append(t_cbuffer *cbuf, char *str, int len);
int						cbuf_nread(t_cbuffer *cbuf, int n, char *str);
int						cbuf_cmdread(t_cbuffer *cbuf, char *str);

void					parse_input(t_env *e, char *line);

int						connect_to_server(t_env *e, char *ip, int port);

int						recvcmd_msg(void *e, int fdsender, char *args);

#endif