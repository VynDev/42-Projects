#include "libft.h"
#include "ft_irc_server.h"

void		init_fdset(t_env *e)
{
	int			i;

	FD_ZERO(&(e->fdset_read));
	FD_ZERO(&(e->fdset_write));
	e->fdset_max = 0;
	i = 0;
	while (i != e->maxsock)
	{
		if (e->socks[i].type != SOCKTYPE_NONE)
		{
			FD_SET(i, &(e->fdset_read));
			e->fdset_max = i;
		}
		++i;
	}
}