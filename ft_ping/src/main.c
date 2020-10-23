#include "libft.h"
#include "ft_ping.h"

t_env				*get_env()
{
	static t_env	*e = NULL;

	if (e == NULL)
		e = (t_env *)malloc(sizeof(t_env));
	return (e);
}

void			print_usage(int argc, char **argv)
{
	ft_printf("Usage: %s [-h] destination\n", argc > 0 ? argv[0] : "");
}

void			parse_args(t_env *e, int argc, char **argv)
{
	int		i;

	ft_strcpy(e->dst_ip, "");
	i = 1;
	while (i != argc)
	{
		if (ft_strlen(argv[i]) > 0 && argv[i][0] != '-')
		{
			ft_strcpy(e->dst_ip, argv[i]);
		}
		else if (!ft_strcmp(argv[i], "-h"))
			e->param_help = 1;
		++i;
	} 
}

int				main(int argc, char **argv)
{
	t_env	*e;
	if (getuid() != 0)
	{
		ft_printf("You must be root to execute this program\n");
		return (0);
	}
	e = get_env();
	init_env(e);
	parse_args(e, argc, argv);
	if (!ft_strlen(e->dst_ip) || e->param_help)
	{
		print_usage(argc, argv);
		exit (0);
	}
	if (signal(SIGALRM, &handler_send) == SIG_ERR || signal(SIGINT, &handler_send) == SIG_ERR)
	{
		perror("signal");
		return (0);
	}
	init_socket(e);
	ping_send(e);
	while (2)
		ping_recv(e);
	free_env(e);
	return (0);
}