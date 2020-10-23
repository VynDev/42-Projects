#include "libft.h"
#include "ft_ping.h"

int             set_addr(t_env *e)
{
	struct addrinfo *res;
	struct addrinfo hints;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_flags = AI_V4MAPPED | AI_ADDRCONFIG | AI_CANONNAME;
	hints.ai_addrlen = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;
	if (getaddrinfo(e->dst_ip, NULL, &hints, &res))
	{
		//ft_printf("getaddrinfo problem\n");
		return (1);
	}
	if (!res)
	{
		//ft_printf("res is null\n");
		return (2);
	}
	e->sin.sin_family = AF_INET;
	e->sin.sin_port = 0;
	e->sin.sin_addr.s_addr = ((struct sockaddr_in *)res->ai_addr)->sin_addr.s_addr;
	return (0);
}

int				init_socket(t_env *e)
{
	int val;

	if ((e->sockfd = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)     
	{
		perror("Failed to create socket");
		exit(1);
	}
	val = 1;
	if (setsockopt(e->sockfd, IPPROTO_IP, IP_HDRINCL, &val, sizeof (val)) < 0)
	{
		perror("Error setting IP_HDRINCL");
		exit(2);
	}
	if (set_addr(e))
	{
		ft_printf("Can't resolve address %s\n", e->dst_ip);
		exit(3);
	}
	return (0);
}
