#include "libft.h"
#include "ft_irc_server.h"

int			sendmsg_to_channel(t_env *e, int fdsender, char* text, char *channel_name)
{
	t_packet	packet;
	char		strcommand[MESSAGE_MAXLENGTH];
	int			i;
	t_channel	*channel;

	if (channel_name[0] == '%')
		channel = e->socks[fdsender].user.channel;
	else
		channel = get_channel(e, channel_name);
	if (!channel)
	{
		if (e->log)
			ft_printf("[LOG] The channel %s doesn't exist\n", channel_name);
		return (0);
	}
	ft_strcpy(strcommand, "/msg ");
	if (fdsender == -1)
		ft_strcat(strcommand, ".");
	else
		ft_strcat(strcommand, e->socks[fdsender].user.nickname);
	ft_strcat(strcommand, " ");
	ft_strcat(strcommand, channel->name);
	ft_strcat(strcommand, " ");
	ft_strcat(strcommand, text);
	if (e->log)
		ft_printf("[LOG] Send from user %s to channel %s : %s\n", fdsender == -1 ? ">SERVER<" : e->socks[fdsender].user.nickname, channel->name, text);
	create_packet(&packet, strcommand, ft_strlen(strcommand) + 1, PROTO_TYPE_TEXT);
	i = 0;
	while (i != SERVER_MAXUSERSPERCHANNEL)
	{
		if (channel->users[i] != 0)
			send_packet(channel->users[i], &packet);
		++i;
	}
	return (1);
}