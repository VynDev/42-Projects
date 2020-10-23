#include "libft.h"
#include "ft_irc_server.h"

char*		get_text(char *args)
{
	int		i;
	char	*target;

	i = 0;
	while (args[i] && args[i] != ' ')
		++i;
	++i;
	while (args[i] && args[i] != ' ')
		++i;
	++i;
	while (args[i] && args[i] != ' ')
		++i;
	++i;
	target = args + i;
	return (target);
}

char*		get_target(char *args)
{
	int		i;
	char	*target;

	i = 0;
	while (args[i] && args[i] != ' ')
		++i;
	++i;
	while (args[i] && args[i] != ' ')
		++i;
	++i;
	target = args + i;
	while (args[i] && args[i] != ' ')
		++i;
	args[i] = '\0';
	return (target);
}

char*		get_sender(char *args)
{
	int		i;
	char	*sender;

	i = 0;
	while (args[i] && args[i] != ' ')
		++i;
	++i;
	sender = args + i;
	while (args[i] && args[i] != ' ')
		++i;
	args[i] = '\0';
	return (sender);
}

int			recvcmd_msg(void *e, int fdsender, char *args)
{
	(void)e;(void)fdsender;(void)args;
	char		*text;
	char		*target;
	char		*sender;

	text = get_text(args);
	target = get_target(args);
	sender = get_sender(args);
	if (target[0] == '#' && sender[0] == '.')
		ft_printf("[%s] %s\n", target, text);
	else if (target[0] == '#')
		ft_printf("[%s] %s : %s\n", target, sender, text);
	else if (sender[0] == '.')
		ft_printf("[SERVER] %s\n", text);
	else
		ft_printf("*PM* %s : %s\n", sender, text);
	return (1);
}