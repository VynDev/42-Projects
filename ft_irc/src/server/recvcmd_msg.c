#include "libft.h"
#include "ft_irc_server.h"

int			recvcmd_msg(void *ee, int fdsender, char *args)
{
	char		*text;
	char		*target;
	t_env		*e;

	e = ee;
	if (get_args(e, args, 3) != 3)
	{
		if (e->log)
			ft_printf("[LOG] command \"/msg\" is missing argument(s)\n");
		sendmsg_to_user(e, -1, "command \"/msg\" is missing argument(s)", e->socks[fdsender].user.nickname);
		return (0);
	}
	print_memslots(e, 3);
	target = (char *)e->memslots[1];
	text = (char *)e->memslots[2];
	if (target[0] == '#' || target[0] == '%')
	{
		if (!sendmsg_to_channel(e, fdsender, text, target))
			sendmsg_to_user(e, -1, "You are not in the channel", e->socks[fdsender].user.nickname);
	}
	else
	{
		if (!sendmsg_to_user(e, fdsender, text, target))
			sendmsg_to_user(e, -1, "This user doesn't exist", e->socks[fdsender].user.nickname);
	}
	return (1);
}