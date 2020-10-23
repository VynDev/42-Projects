/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:25:05 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 15:59:23 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# define MAJOR(strdev) ((strdev >> 24) & 0xffff)
# define MINOR(strdev) (strdev & 0xffff)
# define ABS(x) ((x < 0) ? -(x) : x)

typedef struct		s_info
{
	int				err;
	char			*path;
	char			*name;
	char			*link;
	struct s_info	*link_info;
	struct stat		st;
	char			*username;
	char			*grpname;
}					t_info;

void				error(char *str);

void				list_dir(t_list *path_list, t_list *args_list);

void				list_dir_ext(t_list *info_list,
		t_list *args_list, int call);

int					get_args(t_list **args_list,
		t_list **path_list, int argc, char **argv);

t_list				*print_dir(t_list *lst, t_list *args_list);

t_info				*get_info(char *dir_name, char *file);

t_list				*get_dir(char *dir_name, int hiden);

char				*get_time(const time_t sec);

int					get_slash(char *str);

int					get_maxlinklen(t_list *lst);

int					get_maxsizelen(t_list *lst);

int					get_maxuserlen(t_list *lst);

int					get_maxgrplen(t_list *lst);

int					get_usedblock(t_list *lst);

void				sort_list(t_list *lst, t_list *args_list);

int					is_arg(char c);

int					arg_exist(t_list *args_list, char c);

int					is_dir(t_info *info);

int					is_dirlink(t_info *info);

void				*custom_malloc(size_t size);

void				del_info(void *ptr, size_t size);

void				del_path(void *ptr, size_t size);

void				del_nothing(void *ptr, size_t size);

void				delete_tab(char **tab);

void				get_maxlen(t_list *lst, int *max);

void				print_color(t_info *info, t_list *args_list);

void				reset_color(t_info *info, t_list *args_list);

#endif
