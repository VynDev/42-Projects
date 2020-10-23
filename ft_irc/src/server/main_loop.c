#include "libft.h"
#include "ft_irc_server.h"

void		main_loop(t_env *e)
{
	while (1)
	{
		init_fdset(e);
		select(e->fdset_max + 1, &(e->fdset_read), NULL, NULL, NULL);
		read_fds(e);
	}
}