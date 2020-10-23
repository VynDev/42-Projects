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

char	*add_to_path(char *path, char *filename)
{
	char	*returned_path;

	returned_path = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(filename) + 2));
	ft_strcpy(returned_path, path);
	ft_strcat(returned_path, "/");
	ft_strcat(returned_path, filename);
	return (returned_path);
}

char	*get_right_path(char *filename, char **env)
{
	char	*returned_path;
	char	**tab_path;
	char	**tab_path_root;

	if (!filename)
		return (NULL);
	if (ft_strchr(filename, '/') && !access(filename, F_OK))
		return(ft_strdup(filename));
	else if (!ft_strchr(filename, '/'))
	{
		tab_path = ft_strsplit(ft_env_getvalue(env, "PATH"), ':');
		tab_path_root = tab_path;
		ft_printf("Searshing in PATH\n");
		while (*tab_path)
		{
			returned_path = add_to_path(*tab_path, filename);
			ft_printf("%s\n", returned_path);
			if (!access(returned_path, F_OK))
			{
				ft_tabdel(tab_path_root);
				return (returned_path);
			}		
			free(returned_path);
			++tab_path;
		}
		ft_tabdel(tab_path_root);
	}
	return(NULL);
}
