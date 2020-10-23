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

#ifndef FT_IRC_SERVER_H
# define FT_IRC_SERVER_H
# include "ft_irc.h"

# define SERVER_MAXCHANNELS 1
# define SERVER_MAXUSERSPERCHANNEL 2

# define CHANNEL_FREE 0
# define CHANNEL_USED 1

# define ENV_MAXMEMSLOTS 5

struct s_channel;

typedef struct			s_user
{
	char				nickname[10];
	struct s_channel	*channel;
}						t_user;

typedef struct			s_channel
{
	int					state;
	char				name[16];
	int					*users;
}						t_channel;

typedef struct			s_sock
{
	char 				type;
	int					fd;
	t_cbuffer			*cbuf;
	t_packet			packet;
	t_user				user;
}						t_sock;

typedef struct			s_env
{
	t_sock				*socks;
	int					maxsock;
	fd_set				fdset_read;
	fd_set				fdset_write;
	int					fdset_max;
	t_channel			*channels;
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
void					clear_sock(int fd, t_env *e);
void					get_message(t_env *e, int fdsender, char *buffer, int len);
//int						exec_command(t_env *e, int fdsender, t_message *message);

int						get_args(t_env *e, char *str, int nb);
void					print_memslots(t_env *e, int nb);

t_cbuffer				*cbuf_create(int size);
int						cbuf_append(t_cbuffer *cbuf, char *str, int len);
int						cbuf_nread(t_cbuffer *cbuf, int n, char *str);
int						cbuf_cmdread(t_cbuffer *cbuf, char *str);

t_channel				*get_channel(t_env *e, char *channel_name);
int						sendmsg_to_channel(t_env *e, int fdsender, char* text, char *channel_name);
int						sendmsg_to_user(t_env *e, int fdsender, char* text, char *nickname);

int						recvcmd_msg(void *e, int fdsender, char *args);
int						recvcmd_join(void *e, int fdsender, char *args);
int						recvcmd_leave(void *e, int fdsender, char *args);
int						recvcmd_nick(void *e, int fdsender, char *args);
int						recvcmd_who(void *e, int fdsender, char *args);

t_channel				*get_channel(t_env *e, char *channel_name);
t_channel				*create_channel(t_env *e, char *channel_name);

int						user_leavechannel(t_env *e, int fd);
int						user_joinchannel(t_env *e, int fd, char *channel_name);

#endif