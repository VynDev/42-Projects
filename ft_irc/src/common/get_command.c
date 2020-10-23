#include "libft.h"
#include "ft_irc.h"

extern	t_tab_command	g_tab_command[];

int						ft_cmdlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
		++i;
	return (i);
}

int						(*get_command(char *command))(void *, int, char *)
{
	int		i;

	i = 0;
	while (g_tab_command[i].name != NULL)
	{
		if ((unsigned int)ft_cmdlen(command) == ft_strlen(g_tab_command[i].name) && ft_strncmp(g_tab_command[i].name, command, ft_cmdlen(command)) == 0)
			return (g_tab_command[i].func);
		++i;
	}
	return (NULL);
}
