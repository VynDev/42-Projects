#include "libft.h"
#include "ft_irc_server.h"

int			nick_exists(t_env *e, char *nickname)
{
	int		i;

	i = 0;
	while (i != e->maxsock)
	{
		if (ft_strcmp(e->socks[i].user.nickname, nickname) == 0)
			return (1);
		++i;
	}
	return (0);

}

char*		get_newnick(char *args)
{
	int		i;

	i = 0;
	while (args[i] && args[i] != ' ')
		++i;
	return (args + i + 1);
}

int			recvcmd_nick(void *ee, int fdsender, char *args)
{
	t_env	*e;
	char	old_nick[NICKNAME_MAXLENGTH + 1];
	char	*new_nick;
	char	text[MESSAGE_MAXLENGTH];

	e = (t_env *)ee;
	new_nick = get_newnick(args);
	if (ft_strlen(new_nick) > NICKNAME_MAXLENGTH)
	{
		if (e->log) 
			ft_printf("[LOG] User %s can't changes his nickname because %s is too long\n", e->socks[fdsender].user.nickname, new_nick);
		sendmsg_to_user(e, -1, "The maximum size for a nickname is 9 characters", e->socks[fdsender].user.nickname);
		return (0);
	}
	else if (nick_exists(e, new_nick))
	{
		if (e->log) 
			ft_printf("[LOG] User %s can't changes his nickname because %s is already taken\n", e->socks[fdsender].user.nickname, new_nick);
		sendmsg_to_user(e, -1, "This nickname is already used", e->socks[fdsender].user.nickname);
		return (0);
	}
	ft_strcpy(old_nick, e->socks[fdsender].user.nickname);
	ft_strcpy(e->socks[fdsender].user.nickname, new_nick);
	if (e->socks[fdsender].user.channel)
	{
		ft_strcpy(text, old_nick);
		ft_strcat(text, " is now known as ");
		ft_strcat(text, new_nick);
		if (e->log) 
			ft_printf("[LOG] %s\n", text);
		sendmsg_to_channel(e, -1, text, e->socks[fdsender].user.channel->name);
	}
	return (1);
}