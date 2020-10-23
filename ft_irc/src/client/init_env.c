#include "libft.h"
#include "ft_irc_client.h"

void		init_env(t_env *e)
{
	e->debug = 0;
	e->log = 0;
	e->memslots = (void **)malloc(sizeof(void *) * ENV_MAXMEMSLOTS);
	cv_exit(e->memslots, NULL, "malloc memslots");
	e->sock = (t_sock *)malloc(sizeof(t_sock));
	cv_exit(e->sock, NULL, "malloc sock");
	e->sock->type = SOCK_FREE;
	e->sock->cbuf = cbuf_create(BUF_SIZE);
	e->sock->w_cbuf = cbuf_create(BUF_SIZE);
	e->sock->packet.is_free = 1;
}

void		free_env(t_env *e)
{
	free(e->memslots);
	free(e->sock->cbuf);
	free(e->sock->w_cbuf);
	free(e->sock);
}