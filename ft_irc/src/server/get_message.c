#include "libft.h"
#include "ft_irc_server.h"

t_tab_command	g_tab_command[20] = {
	{"/msg", &recvcmd_msg},
	{"/nick", &recvcmd_nick},
	{"/join", &recvcmd_join},
	{"/leave", &recvcmd_leave},
	{"/who", &recvcmd_who},
	{NULL, NULL}
};

void		get_message(t_env *e, int fdsender, char *buffer, int len)
{
	t_packet		*packet;
	int				(*func)(void *, int, char *);
	int				ret;

	if (e->debug)
		ft_printf("[DEBUG] New message (%d B): %.*s\n", len, len, buffer);
	cbuf_append(e->socks[fdsender].cbuf, buffer, len);
	while ((ret = get_packet(&(e->socks[fdsender].packet), e->socks[fdsender].cbuf)) > 0)
	{
		packet = &(e->socks[fdsender].packet);
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
		else if (e->log)
			ft_printf("[LOG] Unknown command %s for user %s\n", packet->content, e->socks[fdsender].user.nickname);
	}
	if (ret == -1)
	{
		if (e->log)
			ft_printf("[LOG] Message too long for user %s, closing socket\n", e->socks[fdsender].user.nickname);
		clear_sock(fdsender, e);
	}
}