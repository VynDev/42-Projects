#include "libft.h"
#include "ft_irc_server.h"

int			recvcmd_who(void *ee, int fdsender, char *args)
{
	t_env	*e;
	int		i;
	char	text[MESSAGE_MAXLENGTH];
	int		first;

	e = ee;
	(void)args;
	if (e->socks[fdsender].user.channel == NULL)
	{
		if (e->log) 
			ft_printf("[LOG] User %s is not in any channel (/who)\n", e->socks[fdsender].user.nickname);
		sendmsg_to_user(e, -1, "You are not in any channel", e->socks[fdsender].user.nickname);
		return (1);
	}
	i = 0;
	first = 1;
	while (i != SERVER_MAXUSERSPERCHANNEL)
	{
		if (e->socks[fdsender].user.channel->users[i] != 0)
		{
			if (first && !(first = 0))
				ft_strcpy(text, e->socks[e->socks[fdsender].user.channel->users[i]].user.nickname);
			else
			{
				ft_strcat(text, "\n");
				ft_strcat(text, e->socks[e->socks[fdsender].user.channel->users[i]].user.nickname);
			}
		}
		++i;
	}
	sendmsg_to_user(e, -1, text, e->socks[fdsender].user.nickname);
	return (1);
}