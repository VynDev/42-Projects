#include "libft.h"
#include "ft_irc.h"

int			send_packet(int fd, t_packet *packet)
{
	char		*b_packet;

	b_packet = (char *)build_packet(packet);
	return(send(fd, b_packet, MIN_BUF_SIZE + packet->size, 0));
}