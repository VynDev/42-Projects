#include "libft.h"
#include "ft_irc_server.h"

void		fill_packet(t_packet *packet, t_cbuffer *cbuf)
{
	char		buffer[MESSAGE_MAXLENGTH];
	int			ret;

	ret = cbuf_nread(cbuf, packet->size - packet->curr_size, buffer);
	memcpy(packet->content + packet->curr_size, buffer, ret);
	packet->curr_size += ret;
}

void		fill_header(t_packet *packet, t_cbuffer *cbuf)
{
	char		buffer[MIN_BUF_SIZE];

	cbuf_nread(cbuf, sizeof(buffer), buffer);
	extract_packetheader(packet, buffer);
}

int			get_packet(t_packet *packet, t_cbuffer *cbuf)
{
	if (packet->is_free && (unsigned)cbuf->len >= MIN_BUF_SIZE)
	{
		fill_header(packet, cbuf);
		packet->is_free = 0;
		packet->curr_size = 0;
		if (packet->size > MESSAGE_MAXLENGTH)
			return (-1);
	}
	if (!packet->is_free)
	{
		if (packet->curr_size < packet->size)
			fill_packet(packet, cbuf);
	}
	if (!packet->is_free && packet->curr_size == packet->size)
	{
		packet->is_free = 1;
		return (1);
	}
	return (0);
}