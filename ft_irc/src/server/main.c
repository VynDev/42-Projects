#include "libft.h"
#include "ft_irc_server.h"

void			parse_args(t_env *e, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i != argc)
	{
		if (ft_strcmp(argv[i], "-debug") == 0)
			e->debug = 1;
		if (ft_strcmp(argv[i], "-log") == 0)
			e->log = 1;
		++i;
	}
}

int				main(int argc, char **argv)
{
	(void)argc;(void)argv;
	t_env		e;

	init_env(&e);
	parse_args(&e, argc, argv);
	init_server(&e);
	main_loop(&e);
	return (0);
}