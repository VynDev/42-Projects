#include "libft.h"
#include "ft_irc_client.h"

void		init_fdset(t_env *e)
{
	FD_ZERO(&(e->fdset_read));
	FD_ZERO(&(e->fdset_write));
	FD_SET(e->sock->fd, &(e->fdset_read));
	FD_SET(0, &(e->fdset_read));
	e->fdset_max = e->sock->fd;
}