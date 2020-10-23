#include "libft.h"
#include "ft_ping.h"

int				init_env(t_env *e)
{
	e->param_help = 0;
	ft_strcpy(e->src_ip, "0.0.0.0");
	e->datalen = 56;
	e->buffer = (char *)malloc(sizeof(struct iphdr) + sizeof(struct icmphdr) + e->datalen);
	ft_memset(e->buffer, 0, sizeof(struct iphdr) + sizeof(struct icmphdr));
	e->ip = (struct iphdr *)e->buffer;
	e->icmp = (struct icmphdr *)(e->buffer + sizeof(struct iphdr));
	e->data = (e->buffer + sizeof(struct iphdr) + sizeof(struct icmphdr));
	e->seq = 0;
	e->packet_id = 42;
	/*
	**	Statistics
	*/
	e->nbpacket_sent = 0;
	e->nbpacket_received = 0;
	e->ltime_sum = 0;
	e->ltime_min = -1;
	e->ltime_max = -1;
	return (0);
}

int				free_env(t_env *e)
{
	free(e->buffer);
	free(e);
	return (0);
}