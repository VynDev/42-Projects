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

#ifndef FT_IRC_H
# define FT_IRC_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>          /* See NOTES */
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/resource.h>

# define SOCKTYPE_NONE 0
# define SOCKTYPE_SERVER 1
# define SOCKTYPE_CLIENT 2

# define SOCK_FREE 0
# define SOCK_USED 1

# define MESSAGE_MAXLENGTH 512 // RFC 1459
# define CHANNEL_MAXLENGTH 16
# define NICKNAME_MAXLENGTH 9

# define PORT 8888

# define MIN_BUF_SIZE 12

# define BUF_SIZE MIN_BUF_SIZE + MESSAGE_MAXLENGTH

# define PROTO_VERSION 1542
# define PROTO_TYPE_RESPONSE 0
# define PROTO_TYPE_TEXT 1
# define PROTO_TYPE_FILE 2

# define ERR_JOIN_CHANNELFULL
# define ERR_JOIN_WRONGNAME
# define ERR_MSG_NOTINCHANNEL
# define ERR_MSG_DOESNTEXIST
# define ERR_NICK_ALREADYUSED

typedef struct			s_packet
{
	int					is_free;
	int					version; /* header offset 0*/
	int					size; /* header offset 4 */
	int					type; /* header offset 8 */
	int					curr_size;
	char				content[MESSAGE_MAXLENGTH]; /* header offset 12 */
}						t_packet;

typedef struct			s_cbuffer
{
	char				*buf;
	int					size;
	int					len;
	int					r_cur;
	int					w_cur;
}						t_cbuffer;

typedef struct			s_tab_command
{
	char				*name;
	int					(*func)(void *, int, char *);
}						t_tab_command;

int						(*get_command(char *command))(void *, int, char *);

void					create_packet(t_packet *packet, char *data, int len, int type); /* Create packet from data */
void					*build_packet(t_packet *packet); /* return data to send */
void					extract_packet(t_packet *packet, void *b_packet); /* Fill packet from data */
void					extract_packetheader(t_packet *packet, void *b_packet); /* Fill packet header from data*/

int						get_packet(t_packet *packet, t_cbuffer *cbuf);
int						send_packet(int fd, t_packet *packet);

#endif