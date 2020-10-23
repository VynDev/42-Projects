#include "libft.h"
#include "ft_irc_client.h"

void		clear_sock(t_env *e)
{
	ft_printf("Disconnected from the server\n");
	e->sock->type = SOCK_FREE;
	close(e->sock->fd);
	e->sock->cbuf->len = 0;
	e->sock->cbuf->r_cur = 0;
	e->sock->cbuf->w_cur = 0;
	e->sock->w_cbuf->len = 0;
	e->sock->w_cbuf->r_cur = 0;
	e->sock->w_cbuf->w_cur = 0;
}

void		read_fds(t_env *e)
{
	int			ret;
	char		buffer[BUF_SIZE];
	char		*line;

	if (e->sock->type == SOCK_USED && FD_ISSET(e->sock->fd, &(e->fdset_read)))
	{
		ret = recv(e->sock->fd, buffer, BUF_SIZE - e->sock->cbuf->len, 0);
		c_exit(ret, -1, "recv");
		if (ret == 0)
			clear_sock(e);
		else
			get_message(e, e->sock->fd, buffer, ret);
	}
	if (FD_ISSET(0, &(e->fdset_read)))
	{
		get_next_line(0, &line);
		if (ft_strlen(line) + 1 > MESSAGE_MAXLENGTH)
			ft_printf("Message too long\n");
		else
			parse_input(e, line);
		free(line);
	}
}