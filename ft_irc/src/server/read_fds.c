#include "libft.h"
#include "ft_irc_server.h"

void		accept_sock(int fd, t_env *e)
{
	int					csock;
	struct sockaddr_in	csin;
	socklen_t			clen;
	char				*tmp;

	clen = sizeof(csin);
	csock = accept(fd, (struct sockaddr *)&csin, &clen);
	if (csock == -1)
	{
		if (e->log)
			ft_printf("[LOG] New user connection ERROR\n");
		return ;
	}
	e->socks[csock].type = SOCKTYPE_CLIENT;
	ft_strcpy(e->socks[csock].user.nickname, "Guest");
	tmp = ft_itoa(csock);
	ft_strcat(e->socks[csock].user.nickname, tmp);
	free(tmp);
	e->socks[csock].user.channel = NULL;
	if (e->log)
		ft_printf("[LOG] New user connected (%s)\n", e->socks[csock].user.nickname);
}

void		clear_sock(int fd, t_env *e)
{
	recvcmd_leave(e, fd, NULL);
	if (e->log)
		ft_printf("[LOG] User %s (%d) disconnected from the server\n", e->socks[fd].user.nickname, fd);
	e->socks[fd].type = SOCKTYPE_NONE;
	user_leavechannel(e, fd);
	close(fd);
	e->socks[fd].cbuf->len = 0;
	e->socks[fd].cbuf->r_cur = 0;
	e->socks[fd].cbuf->w_cur = 0;
}

void		read_fds(t_env *e)
{
	int			i;
	int			ret;
	char		buffer[BUF_SIZE];

	i = 0;
	while (i != e->maxsock)
	{
		if (FD_ISSET(i, &(e->fdset_read)) && e->socks[i].type == SOCKTYPE_SERVER)
		{
			if (e->log)
				ft_printf("[LOG] New user trying to connect\n");
			accept_sock(i, e);
		}
		else if (FD_ISSET(i, &(e->fdset_read)) && e->socks[i].type == SOCKTYPE_CLIENT)
		{
			ret = recv(i, buffer, BUF_SIZE - e->socks[i].cbuf->len, 0);
			c_exit(ret, -1, "recv");
			if (ret == 0)
				clear_sock(i, e);
			else
				get_message(e, i, buffer, ret);
		}
		++i;
	}
}