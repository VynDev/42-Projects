/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:23:14 by xesnault          #+#    #+#             */
/*   Updated: 2017/02/13 12:44:10 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				print_color(t_info *info, t_list *args_list)
{
	int		access;

	if (!arg_exist(args_list, 'G'))
		return ;
	access = info->st.st_mode;
	if (info->link)
		ft_printf("{magenta}");
	else if (is_dir(info))
		ft_printf("{blue}");
	else if ((access & S_IXUSR) || (access & S_IXGRP) || (access & S_IXOTH))
		ft_printf("{red}");
}

void				reset_color(t_info *info, t_list *args_list)
{
	int		access;

	if (!arg_exist(args_list, 'G'))
		return ;
	access = info->st.st_mode;
	if (info->link)
		ft_printf("{eoc}");
	else if (is_dir(info))
		ft_printf("{eoc}");
	else if ((access & S_IXUSR) || (access & S_IXGRP) || (access & S_IXOTH))
		ft_printf("{eoc}");
}
