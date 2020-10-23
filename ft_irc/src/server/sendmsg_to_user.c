#include "libft.h"
#include "ft_irc_server.h"

int			sendmsg_to_user(t_env *e, int fdsender, char* text, char *nickname)
{
	t_packet	packet;
	char		strcommand[MESSAGE_MAXLENGTH];
	int			i;

	ft_strcpy(strcommand, "/msg ");
	if (fdsender == -1)
		ft_strcat(strcommand, ".");
	else
		ft_strcat(strcommand, e->socks[fdsender].user.nickname);
	ft_strcat(strcommand, " ");
	ft_strcat(strcommand, nickname);
	ft_strcat(strcommand, " ");
	ft_strcat(strcommand, text);
	if (e->log)
		ft_printf("[LOG] Send from user %s to user %s : %s\n", fdsender == -1 ? ">SERVER<" : e->socks[fdsender].user.nickname, nickname, text);
	create_packet(&packet, strcommand, ft_strlen(strcommand) + 1, PROTO_TYPE_TEXT);
	i = 0;
	while (i != e->maxsock)
	{
		if (e->socks[i].type == SOCKTYPE_CLIENT && ft_strcmp(e->socks[i].user.nickname, nickname) == 0)
		{
			send_packet(i, &packet);
			return (1);
		}
		++i;
	}
	if (e->log)
		ft_printf("[LOG] This user %s doesn't exist\n", nickname);
	return (0);
}