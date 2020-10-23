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

void	do_command(char *line, t_data *data)
{
	char	**command;
	char	*file;
	int		status;

	command = split_wsquote(line);
	ft_tabdelch(command, '"');
	if (!command[0])
	{
		ft_tabdel(command);
		return ;
	}
	if (!do_builtin(command))
	{
		file = get_right_path(command[0], data->env);
		if (file_check(file, command[0]))
		{
			ft_printf("Program executed\n");
			if ((data->fork_pid = fork()) == 0)
			{
				execve(file, command, data->env);
				ft_printf("Cannot execute this file\n");
				exit(0);
			}
			wait(&status);
			data->fork_pid = 0;
			if (WIFSIGNALED(status) && WTERMSIG(status) == 11)
				print_error("===> SEGFAULT :D", NULL);
		}
		if (file)
			free(file);
	}
	ft_tabdel(command);
}

void	get_commands(char *line, t_data	*data)
{
	char	**commands;
	int		i;

	i = 0;
	commands = ft_strsplit_quote(line, ';');
	while(commands[i])
	{
		do_command(commands[i], data);
		++i;
	}
	ft_tabdel(commands);
}
