#include "libft.h"
#include "ft_ping.h"

void		print_stats(t_env *e)
{
	float a;
	float b;
	float c;

	if (e->ltime_min == -1)
		return ;
	ft_printf("\n--- %s ping statistics ---\n", e->dst_ip);
	a = e->nbpacket_received;
	b = e->nbpacket_sent;
	c = a / b;
	ft_printf("%d packets transmitted, %d received, %d%% packet loss\n", e->nbpacket_sent, e->nbpacket_received, 100 - (int)(c * 100));
	ft_printf("rtt min/avg/max = %d/%u/%d ms\n", e->ltime_min, e->ltime_sum / e-> nbpacket_sent, e->ltime_max);
}