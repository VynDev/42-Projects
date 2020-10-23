#include "libft.h"
#include "ft_ping.h"

int				set_iphdr(t_env *e)
{
	e->ip->ihl = 5;
	e->ip->version = 4;
	e->ip->tos = 0;
	e->ip->tot_len = sizeof (struct iphdr) + sizeof (struct icmphdr) + e->datalen;
	e->ip->id = 0;
	e->ip->frag_off = 0;
	e->ip->ttl = 64;
	e->ip->protocol = IPPROTO_ICMP;
	e->ip->check = 0;
	e->ip->saddr = inet_addr(e->src_ip);
	e->ip->daddr = e->sin.sin_addr.s_addr;
	e->ip->check = in_cksum((unsigned short *)e->buffer, sizeof (struct iphdr));
	return (1);
}

int				set_icmphdr(t_env *e)
{
	e->icmp->type = ICMP_ECHO;
	e->icmp->un.echo.id = e->packet_id;
	e->icmp->un.echo.sequence = (e->seq << 8) | (e->seq >> 8);
	e->icmp->checksum = 0;
	e->icmp->checksum = in_cksum((unsigned short *)e->icmp, sizeof(struct icmphdr) + e->datalen);
	return (1);
}