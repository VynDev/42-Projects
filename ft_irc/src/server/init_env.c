#include "libft.h"
#include "ft_irc_server.h"

void		init_env(t_env *e)
{
	struct rlimit	rl;
	int				i;
	int				j;

	e->debug = 0;
	e->log = 0;
	c_exit(getrlimit(RLIMIT_NOFILE, &rl), -1, "getrlimit");
	e->maxsock = rl.rlim_cur;
	ft_printf("Max fd is %d\n", e->maxsock);
	e->socks = (t_sock *)malloc(sizeof(t_sock) * e->maxsock);
	cv_exit(e->socks, NULL, "malloc socks");
	e->memslots = (void **)malloc(sizeof(void *) * ENV_MAXMEMSLOTS);
	cv_exit(e->memslots, NULL, "malloc memslots");
	i = 0;
	while (i != e->maxsock)
	{
		e->socks[i].type = SOCKTYPE_NONE;
		e->socks[i].packet.is_free = 1;
		e->socks[i].cbuf = cbuf_create(BUF_SIZE);
		++i;
	}
	e->channels = (t_channel *)malloc(sizeof(t_channel) * SERVER_MAXCHANNELS);
	i = 0;
	while (i != SERVER_MAXCHANNELS)
	{
		e->channels[i].state = CHANNEL_FREE;
		e->channels[i].users = (int*)malloc(sizeof(t_user *) * SERVER_MAXUSERSPERCHANNEL);
		j = 0;
		while (j != SERVER_MAXUSERSPERCHANNEL)
		{
			e->channels[i].users[j] = 0;
			++j;
		}
		++i;
	}
}