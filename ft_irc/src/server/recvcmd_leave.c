#include "libft.h"
#include "ft_irc_server.h"

int			recvcmd_leave(void *e, int fdsender, char *args)
{
	char	text[MESSAGE_MAXLENGTH];
	char	channel_name[CHANNEL_MAXLENGTH];
	int		ret;

	(void)args;
	if (((t_env *)e)->socks[fdsender].user.channel)
	{
		ft_strcpy(channel_name, ((t_env *)e)->socks[fdsender].user.channel->name);
		if ((ret = user_leavechannel(e, fdsender)))
		{
			if (((t_env *)e)->log) 
				ft_printf("[LOG] User %s left channel %s\n", ((t_env *)e)->socks[fdsender].user.nickname, channel_name);
			ft_strcpy(text, ((t_env *)e)->socks[fdsender].user.nickname);
			ft_strcat(text, " left the channel");
			sendmsg_to_channel(e, -1, text, channel_name);
			return (1);
		}
		else if(((t_env *)e)->log)
			ft_printf("[LOG] An error happened during the join, error code %d\n", ret);
	}
	else
	{
		if (((t_env *)e)->log)
			ft_printf("[LOG] The user %s is not in any channel (/leave)\n", ((t_env *)e)->socks[fdsender].user.nickname);
		sendmsg_to_user(e, -1, "You are not in any channel", ((t_env *)e)->socks[fdsender].user.nickname);
	}
	return (0);
}