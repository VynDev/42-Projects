/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:21:40 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:30:43 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		replace(char removed, char added, t_list *args_list)
{
	while (args_list)
	{
		if ((*(char *)args_list->content) == removed)
		{
			(*(char *)args_list->content) = added;
			return ;
		}
		args_list = args_list->next;
	}
}

static int		add_to_list(t_list **args_list, char *arg)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (!is_arg(arg[i]) || (arg[i] == '-' && ft_strlen(arg) > 2))
		{
			ft_putstr_fd("ft_ls: illegal option -- ", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putchar_fd('\n', 2);
			ft_putstr_fd("usage: ft_ls [-GRalrt] [file ...]\n", 2);
			return (0);
		}
		if (arg[i] == 'l' && arg_exist(*args_list, '1'))
			replace('1', 'l', *args_list);
		else if (arg[i] == '1' && arg_exist(*args_list, 'l'))
			replace('l', '1', *args_list);
		else if (!arg_exist(*args_list, arg[i]))
			ft_lstadd(args_list, ft_lstnew(arg + i, sizeof(char)));
		++i;
	}
	return (1);
}

int				get_args(t_list **args_list,
		t_list **path_list, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0'
				&& !arg_exist(*args_list, '-') && !*path_list)
		{
			if (!add_to_list(args_list, argv[i]))
				return (0);
		}
		else
			ft_lstadd(path_list, ft_lstnew(argv[i], ft_strlen(argv[i]) + 1));
		++i;
	}
	if (!*path_list)
		ft_lstadd(path_list, ft_lstnew(".", sizeof(char) + 1));
	return (1);
}
