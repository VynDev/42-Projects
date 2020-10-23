#include "libft.h"
#include "ft_irc_client.h"

t_tab_command	g_tab_command[20] = {
	{"/msg", &recvcmd_msg},
	{NULL, NULL}
};

void		get_message(t_env *e, int fdsender, char *buffer, int len)
{
	t_packet		*packet;
	int				(*func)(void *, int, char *);

	if (e->debug)
		ft_printf("[DEBUG] New message (%d B): %.*s\n", len, len, buffer);
	cbuf_append(e->sock->cbuf, buffer, len);
	while (get_packet(&(e->sock->packet), e->sock->cbuf))
	{
		packet = &(e->sock->packet);
		if (e->debug)
		{
			ft_printf("[DEBUG] PACKET RECEIVED:\n");
			ft_printf("[DEBUG] Version: %d\n", packet->version);
			ft_printf("[DEBUG] Size: %d\n", packet->size);
			ft_printf("[DEBUG] Type: %d\n", packet->type);
			ft_printf("[DEBUG] Content: %.*s\n", packet->size, packet->content);
		}
		func = get_command(packet->content);
		if (func)
			func((void *)e, fdsender, packet->content);
		else
			ft_printf("Unknown command from server\n");
	}
}