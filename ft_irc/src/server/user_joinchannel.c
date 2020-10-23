#include "libft.h"
#include "ft_irc_server.h"

int			user_joinchannel(t_env *e, int fd, char *channel_name)
{
	t_channel	*channel;
	int			i;

	user_leavechannel(e, fd);
	if ((channel = get_channel(e, channel_name)) == NULL)
	{
		if (!(channel = create_channel(e, channel_name)))
			return (0);
	}
	e->socks[fd].user.channel = channel;
	i = 0;
	while (i != SERVER_MAXUSERSPERCHANNEL)
	{
		if (channel->users[i] == 0)
		{
			channel->users[i] = fd;
			return (1);
		}
		++i;
	}
	return (-1);
}