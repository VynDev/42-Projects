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

int		do_builtin(char **command)
{
	int				i;
	t_tab_builtin	*tab_builtin;

	i = 0;
	tab_builtin	= get_tab_builtin();
	while (tab_builtin[i].command)
	{
		if (!ft_strcmp(command[0], tab_builtin[i].command))
		{
			ft_printf("This is a builtin program\n");
			(*tab_builtin[i].f)(ft_tabcount(command), command);
			return (1);
		}
		++i;
	}
	return (0);
}
