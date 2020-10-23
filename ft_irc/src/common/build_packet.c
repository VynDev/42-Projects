#include "libft.h"
#include "ft_irc_server.h"
#include <errno.h>

void				create_packet(t_packet *packet, char *data, int len, int type)
{
	packet->version = PROTO_VERSION;
	packet->size = len;
	packet->type = type;
	ft_memcpy(packet->content, data, len);
}

void				*build_packet(t_packet *packet)
{
	char			*b_packet;
	int				proto_newpacket;

	proto_newpacket = PROTO_VERSION;
	b_packet = (char *)malloc(MIN_BUF_SIZE + packet->size);
	ft_memcpy(b_packet, &proto_newpacket, sizeof(proto_newpacket));
	ft_memcpy(b_packet + 4, &(packet->size), sizeof(packet->size));
	ft_memcpy(b_packet + 8, &(packet->type), sizeof(packet->type));
	ft_memcpy(b_packet + 12, packet->content, packet->size);
	return (b_packet);
}

void				extract_packet(t_packet *packet, void *b_packet)
{
	ft_memcpy(&(packet->version), b_packet, sizeof(packet->version));
	ft_memcpy(&(packet->size), b_packet + 4, sizeof(packet->size));
	ft_memcpy(&(packet->type), b_packet + 8, sizeof(packet->type));
}

void				extract_packetheader(t_packet *packet, void *b_packet)
{
	ft_memcpy(&(packet->version), b_packet, sizeof(packet->version));
	ft_memcpy(&(packet->size), b_packet + 4, sizeof(packet->size));
	ft_memcpy(&(packet->type), b_packet + 8, sizeof(packet->type));
}