#include "libft.h"
#include "ft_irc_server.h"

int			recvcmd_join(void *e, int fdsender, char *args)
{
	int		i;
	int		ret;
	char	text[MESSAGE_MAXLENGTH];

	i = 0;
	while (args[i] && args[i] != ' ')
		++i;
	++i;
	if (ft_strlen(args + i) < 2 || args[i] != '#')
	{
		if (((t_env *)e)->log)
			ft_printf("[LOG] Channel name must be specified and contains minimum 2 characters (including the starting # character)\n");
		sendmsg_to_user(e, -1, "Channel name must be specified and contains minimum 2 characters (including the starting # character)", ((t_env *)e)->socks[fdsender].user.nickname);
	}
	else if ((ret = user_joinchannel(e, fdsender, args + i)) == 1)
	{
		if (((t_env *)e)->log) 
			ft_printf("[LOG] User %s joined channel %s\n", ((t_env *)e)->socks[fdsender].user.nickname, ((t_env *)e)->socks[fdsender].user.channel->name);
		ft_strcpy(text, ((t_env *)e)->socks[fdsender].user.nickname);
		ft_strcat(text, " joined the channel");
		sendmsg_to_channel(e, -1, text, ((t_env *)e)->socks[fdsender].user.channel->name);
		return (1);
	}
	else
	{
		if (ret == 0)
		{
			if (((t_env *)e)->log)
				ft_printf("[LOG] The server has reached the maximum channel limitaion\n");
			sendmsg_to_user(e, -1, "The server has reached the maximum channel limitaion", ((t_env *)e)->socks[fdsender].user.nickname);
		}
		else if (ret == -1)
		{
			if (((t_env *)e)->log)
				ft_printf("[LOG] The channel has reached the maximum user limitaion\n");
			sendmsg_to_user(e, -1, "The channel has reached the maximum user limitaion", ((t_env *)e)->socks[fdsender].user.nickname);
		}
	}
	return (0);
}