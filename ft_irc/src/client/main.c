#include "libft.h"
#include "ft_irc_client.h"

int				connect_to_server(t_env *e, char *ip, int port)
{
	struct sockaddr_in		sin;
	struct protoent			*pe;
	int						fdsock;

	if (e->sock->type == SOCK_USED)
	{
		close(e->sock->fd);
		e->sock->type = SOCK_FREE;
		e->sock->cbuf->len = 0;
		e->sock->cbuf->r_cur = 0;
		e->sock->cbuf->w_cur = 0;
	}
	pe = getprotobyname("tcp");
	fdsock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_port = htons(port);
	ft_printf("Connecting to %s on port %d\n", ip, port);
	connect(fdsock, (struct sockaddr *)&sin, sizeof(sin));
	e->sock->fd = fdsock;
	e->sock->type = SOCK_USED;

	return (1);
}

void			parse_args(t_env *e, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i != argc)
	{
		if (ft_strcmp(argv[i], "-debug") == 0)
			e->debug = 1;
		if (ft_strcmp(argv[i], "-log") == 0)
			e->log = 1;
		++i;
	}
}

int				main(int argc, char **argv)
{
	(void)argc;(void)argv;
	t_env					e;

	init_env(&e);
	parse_args(&e, argc, argv);
	if (argc > 1)
		connect_to_server(&e, argv[1], (argc > 2 ? ft_atoi(argv[2]) : PORT));
	main_loop(&e);
	return (0);
}