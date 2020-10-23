#include "libft.h"
#include "ft_irc_server.h"

void		channel_removeuser(int fd, t_channel *channel)
{
	int		i;
	int		is_empty;

	i = 0;
	is_empty = 1;
	while (i != SERVER_MAXUSERSPERCHANNEL)
	{
		
		if (channel->users[i] == fd)
			channel->users[i] = 0;
		else if (channel->users[i] != 0)
			is_empty = 0;
		++i;
	}
	if (is_empty)
		channel->state = CHANNEL_FREE;
}

t_channel	*get_channel(t_env *e, char *channel_name)
{
	int		i;

	i = 0;
	while (i != SERVER_MAXCHANNELS)
	{
		if (e->channels[i].state == CHANNEL_USED && ft_strcmp(e->channels[i].name, channel_name) == 0)
			return (e->channels + i);
		++i;
	}
	return (NULL);
}

t_channel	*create_channel(t_env *e, char *channel_name)
{
	int		i;

	i = 0;
	while (i != SERVER_MAXCHANNELS)
	{
		if (e->channels[i].state == CHANNEL_FREE)
		{
			e->channels[i].state = CHANNEL_USED;
			ft_strcpy(e->channels[i].name, channel_name);
			return (e->channels + i);
		}
		++i;
	}
	return (NULL);
}

int			user_leavechannel(t_env *e, int fd)
{
	if (!e->socks[fd].user.channel)
		return (0);
	channel_removeuser(fd, e->socks[fd].user.channel);
	e->socks[fd].user.channel = NULL;
	return (1);
}