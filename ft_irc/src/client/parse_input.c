#include "libft.h"
#include "ft_irc_client.h"

void		exit_client(t_env *e)
{
	free_env(e);
	exit(0);
}

void		parse_input(t_env *e, char *line)
{
	t_packet		packet;
	int				ret;
	char			*alt_line;
	
	if (ft_strcmp(line, "/quit") == 0 && ft_strlen(line) == ft_strlen("/quit"))
	{
		exit_client(e);
	}
	else if (ft_strncmp(line, "/connect ", ft_strlen("/connect ")) == 0 && (ret = get_args(e, line, 3)) > 1)
	{
		connect_to_server(e, e->memslots[1], (ret > 2 ? ft_atoi(e->memslots[2]) : PORT));
		return ;
	}
	else if (ft_strlen(line) > 0 && line[0] == '/')
	{
		create_packet(&packet, line, ft_strlen(line) + 1, PROTO_TYPE_TEXT);
		send_packet(e->sock->fd, &packet);
		return ;
	}
	alt_line = (char *)malloc(sizeof(char) * (ft_strlen(line) + ft_strlen("/msg % ") + 1));
	ft_strcpy(alt_line, "/msg % ");
	ft_strcat(alt_line, line);
	create_packet(&packet, alt_line, ft_strlen(alt_line) + 1, PROTO_TYPE_TEXT);
	send_packet(e->sock->fd, &packet);
	free(alt_line);
}