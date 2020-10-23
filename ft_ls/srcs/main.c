/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:23:05 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:32:39 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error(char *str)
{
	ft_putstr_fd("ls: ", 2);
	perror(str);
}

void	*custom_malloc(size_t size)
{
	void	*returned_ptr;

	returned_ptr = malloc(size);
	if (!returned_ptr)
		exit(1);
	return (returned_ptr);
}

int		main(int argc, char **argv)
{
	t_list *args_list;
	t_list *path_list;

	args_list = NULL;
	path_list = NULL;
	if (!get_args(&args_list, &path_list, argc, argv))
		return (1);
	list_dir(path_list, args_list);
	ft_lstdel(&args_list, &del_path);
	ft_lstdel(&path_list, &del_path);
	return (0);
}
