#include "libft.h"
#include "ft_ping.h"
#include <stdio.h>

void		set_msghdr(t_env *e, struct msghdr *msghdr, char *buffer, char *control_buffer)
{
	msghdr->msg_name = &(e->sin);
	msghdr->msg_namelen = sizeof(struct sockaddr);
	msghdr->msg_control = control_buffer;
	msghdr->msg_controllen = 4046;
	msghdr->msg_iovlen = 1;
	msghdr->msg_iov = (struct iovec *)malloc(sizeof(struct iovec));
	msghdr->msg_iov->iov_base = buffer;
	msghdr->msg_iov->iov_len = 4046;
	msghdr->msg_flags = 0;
}

void		ping_recv(t_env *e)
{
	char			buffer[4046];
	char			control_buffer[4046];
	struct msghdr	msghdr;
	struct timeval	current_time;
	struct iphdr	*ipheader;

	ft_memset(buffer, 0, sizeof(buffer));
	set_msghdr(e, &msghdr, buffer, control_buffer);
	if (recvmsg(e->sockfd, &msghdr, 0) == -1)
	{
		perror("recv");
	}
	else
	{
		if (((struct icmphdr *)(buffer + sizeof(struct iphdr)))->un.echo.id != e->packet_id || ((struct icmphdr *)(buffer + sizeof(struct iphdr)))->type != ICMP_ECHOREPLY)
		{
			free(msghdr.msg_iov);
			return ;
		}
		++(e->nbpacket_received);
		ipheader = (struct iphdr *)buffer;
		struct in_addr *ad = (struct in_addr *)&ipheader->saddr;
		gettimeofday(&current_time, NULL);
		unsigned short tt = ipheader->tot_len;
		int ms = (current_time.tv_usec - e->ltime.tv_usec) / 1000;
		e->ltime_sum += ms;
		if (e->ltime_min == -1 || ms < e->ltime_min)
			e->ltime_min = ms;
		if (e->ltime_max == -1 || ms > e->ltime_max)
			e->ltime_max = ms;
		ft_printf("%hu bytes from %s (%s): icmp_seq=%d ttl=%d time=%lu ms\n", ((tt << 8) | (tt >> 8)) - (int)sizeof(struct iphdr), e->dst_ip, inet_ntoa(*ad), e->seq, ipheader->ttl, ms);
	}
	free(msghdr.msg_iov);
}