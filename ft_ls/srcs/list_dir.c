/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:22:57 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:52:04 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	lstsort_path1(t_list *lst)
{
	if (ft_strcmp(lst->content, lst->next->content) > 0)
		return (1);
	return (0);
}

static void	do_rec(t_list *rec, t_list *args_list)
{
	ft_putchar('\n');
	list_dir_ext(rec, args_list, 1);
	ft_lstdel(&rec, &del_nothing);
}

void		list_dir_ext(t_list *info_list, t_list *args_list, int call)
{
	t_info			*info;
	t_list			*lst;
	t_list			*rec;
	t_list			*root;

	root = info_list;
	while (info_list)
	{
		info = info_list->content;
		if (call != 0 || ft_lstcount(info_list) > 1)
			ft_printf("%s:\n", info->path);
		call = 1;
		lst = get_dir(info->path, arg_exist(args_list, 'a'));
		if (lst && arg_exist(args_list, 'l'))
			ft_printf("total %d\n", get_usedblock(lst));
		sort_list(lst, args_list);
		rec = print_dir(lst, args_list);
		if (rec)
			do_rec(rec, args_list);
		if (info_list->next)
			ft_putchar('\n');
		info_list = info_list->next;
		ft_lstdel(&lst, &del_info);
	}
}

static int	fill_list(t_list **lst,
	t_list **info_list, t_list *path_list, t_list *args_list)
{
	t_info			*info;

	if ((info = get_info(NULL, path_list->content)) == NULL)
	{
		if (ft_strcmp(path_list->content, "") == 0)
		{
			error("fts_open");
			return (0);
		}
		error(path_list->content);
	}
	if (info && is_dirlink(info) && !arg_exist(args_list, 'l'))
		ft_lstaddback(lst, ft_lstnew(info, sizeof(t_info)));
	else if (info && !is_dir(info))
		ft_lstaddback(info_list, ft_lstnew(info, sizeof(t_info)));
	else if (info && is_dir(info))
		ft_lstaddback(lst, ft_lstnew(info, sizeof(t_info)));
	free(info);
	return (1);
}

void		list_dir(t_list *path_list, t_list *args_list)
{
	t_list			*info_list;
	t_list			*lst;
	int				call;

	lst = NULL;
	info_list = NULL;
	call = ft_lstcount(path_list) > 1 ? 1 : 0;
	ft_lstsort(path_list, &lstsort_path1);
	while (path_list)
	{
		if (!fill_list(&lst, &info_list, path_list, args_list))
			return ;
		path_list = path_list->next;
	}
	sort_list(info_list, args_list);
	sort_list(lst, args_list);
	print_dir(info_list, args_list);
	if (info_list && lst)
		ft_putchar('\n');
	list_dir_ext(lst, args_list, call);
	ft_lstdel(&info_list, &del_info);
	ft_lstdel(&lst, &del_info);
}
