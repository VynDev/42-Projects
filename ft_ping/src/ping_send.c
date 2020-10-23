#include "libft.h"
#include "ft_ping.h"

void		handler_send(int sig)
{
	t_env	*e;

	e = get_env();
	if (sig == SIGALRM)
	{
		ping_send(e);
	}
	if (sig == SIGINT)
	{
		print_stats(e);
		exit(0);
	}
}

void		ping_send(t_env *e)
{
	++(e->seq);
	set_icmphdr(e);
	set_iphdr(e);
	if (e->seq == 1)
	{
		ft_printf("PING %s (%s) %d(%d) bytes of data.\n", e->dst_ip, inet_ntoa(e->sin.sin_addr), e->datalen, e->ip->tot_len);
	}
	if (gettimeofday(&(e->ltime), NULL))
	{
		perror("gettimeofday");
		return ;
	}
	if (sendto (e->sockfd, e->buffer, e->ip->tot_len,  0, (struct sockaddr *)&e->sin, sizeof (e->sin)) < 0)
    {
        perror("sendto failed");
        return ;
    }
    ++(e->nbpacket_sent);
    alarm(1);
}