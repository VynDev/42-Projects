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

void	print_error(char *str, char *command)
{
	if (str)
		ft_putstr_fd(str, 2);
	if (command)
		ft_putstr_fd(command, 2);
	ft_putendl_fd("", 2);
}

void	print_env(char **env)
{
	while (*env)
	{
		ft_printf("%s\n", *env);
		++env;
	}
}

void	print_arg(int ac, char **av)
{
	int		i;

	i = 0;
	while (++i < ac)
		ft_printf("%s\n", av[i]);
}
