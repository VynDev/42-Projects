/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:48:24 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:37:40 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/resource.h>
# include <linux/icmp.h>
# include <netinet/ip.h>
# include <sys/time.h>
# include <signal.h>

typedef struct			s_env
{
	int					param_help;
	int					sockfd;
	char				src_ip[32];
	char				dst_ip[32]; /* Can be IPv4 format or domain name */
	struct iphdr		*ip;
	struct icmphdr		*icmp;
	char				*data;
	int					datalen;
	struct sockaddr_in	sin;
	char				*buffer;
	int					seq;
	struct timeval		ltime;
	__be16				packet_id;
	/*
	**	Statistics
	*/
	int					nbpacket_sent;
	int					nbpacket_received;
	unsigned int		ltime_sum;
	int					ltime_min;
	int					ltime_max;
}						t_env;

t_env					*get_env();

int						init_env();
int						init_socket();

int						free_env();

int						set_iphdr(t_env *e);
int						set_icmphdr(t_env *e);

void					handler_send(int sig);
void					ping_send(t_env *e);
void					ping_recv(t_env *e);

void					print_stats(t_env *e);

unsigned short			in_cksum(unsigned short *addr, int len);
unsigned short			csum(unsigned short *ptr,int nbytes);

#endif