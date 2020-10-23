/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:23:05 by xesnault          #+#    #+#             */
/*   Updated: 2017/03/14 09:27:09 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>

 void sigint_handler(int sig)
{
	(void)sig;
}



int		main(int ac, char **av, char **env)
{
	ft_printf("{green}--===Minishell started===--{eoc}\n");
	print_arg(ac, av);
	(void)ac;(void)av;(void)env;
	char	*line;
	t_data	*data;

	data = get_data();
	data_init(env);
//	term_init();
	signal(SIGINT, sigint_handler);
	while (!data->exit_shell)
	{
		ft_printf("{cyan}VynShell>{eoc} ");
		get_input(0, &line);
		if (line)
		{
			get_commands(line, data);
			free(line);
		}
	}
	ft_printf("{green}--===Minishell finished===--{eoc}\n");
	data_free();
//	term_reset();
	return (0);
}
