#include "libft.h"
#include "ft_irc_server.h"

void		init_server(t_env *e)
{
	struct sockaddr_in		sin;
	int						sock;
	struct protoent			*pe;

	pe = getprotobyname("tcp");
	cv_exit(pe, NULL, "getprotobyname");
	sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	e->socks[sock].type = SOCKTYPE_SERVER;
	c_exit(sock, -1, "server socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(PORT);
	c_exit(bind(sock, (struct sockaddr *)&sin, sizeof(sin)), -1, "bind");
	c_exit(listen(sock, 42), -1, "listen");
}