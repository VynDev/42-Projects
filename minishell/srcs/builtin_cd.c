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

static char		*get_dir(t_data *data, int ac, char **av)
{
	char	*dir;

	if (ac > 1 && !ft_strcmp(av[1], "-") && !data->last_dir)
	{
		print_error("cd: This is your first directory", NULL);
		return (NULL);
	}
	if (ac > 1 && !ft_strcmp(av[1], "-"))
		dir = ft_strdup(data->last_dir);
	else if (ac > 1)
		dir = ft_strdup(av[1]);
	else
		dir = ft_strdup(ft_env_getvalue(data->env, "HOME"));
	return (dir);
}

static int		check_dir(char *dir)
{
	int		error;

	error = 0;
	if (access(dir, F_OK) && (error = 1))
		print_error("cd: no such file or directory: ", dir);
	else if (access(dir, X_OK) && (error = 1))
		print_error("cd: Permission denied: ", dir);
	if (error)
		free(dir);
	return (error ? 0 : 1);
}

void			builtin_cd(int ac, char **av)
{
	t_data	*data;
	char	*dir;

	data = get_data();
	if (!(dir = get_dir(data, ac, av)))
		return ;
	if (!check_dir(dir))
		return ;
	if (data->last_dir)
		free(data->last_dir);
	data->last_dir = getcwd(NULL, 0);
	ft_env_setvalue(&(data->env), "OLDPWD", data->last_dir);
	if (chdir(dir))
		print_error("cd: Error chdir", NULL);
	ft_env_setvalue(&(data->env), "PWD", dir);
	free(dir);
}
