 #include "libft.h"
#include "ft_irc_server.h"

int		get_args(t_env *e, char *str, int nb)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (nb != 0)
	{
		e->memslots[k] = str + i;
		if (nb == 1)
			return (k + 1);
		while (str[i] && str[i] != ' ')
			++i;
		if (str[i] == ' ')
		{
			str[i] = '\0';
			++i;
		}
		else
		{
			return (k + (i == 0 ? 0 : 1));
		}
		++k;
		--nb;
	}
	return (0);
}

void	print_memslots(t_env *e, int nb)
{
	int		i;
	i = 0;
	while (i != nb && i != ENV_MAXMEMSLOTS)
	{
		if (e->debug)
			ft_printf("[DEBUG] args[%d]: %s\n", i, e->memslots[i]);
		++i;
	}
}