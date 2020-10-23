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

char	**ft_tabdup(char **tab)
{
	char	**tab_dup;
	int		i;

	if (!(tab_dup = (char **)malloc(sizeof(char *) * (ft_tabcount(tab) + 1))))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		tab_dup[i] = ft_strdup(tab[i]);
		++i;
	}
	tab_dup[i] = 0;
	return (tab_dup);
}

char	**ft_tabadd(char **tab, char *str)
{
	char	**tab_dup;
	int		i;

	if (!(tab_dup = (char **)malloc(sizeof(char *) * (ft_tabcount(tab) + 2))))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		tab_dup[i] = ft_strdup(tab[i]);
		++i;
	}
	tab_dup[i] = ft_strdup(str);
	tab_dup[i + 1] = 0;
	ft_tabdel(tab);
	return (tab_dup);
}

char	*ft_env_getvalue(char **env, char *key)
{
	int		len;

	len = ft_strlen(key);
	while (*env)
	{
		if (!ft_strncmp(*env, key, len) && *((*env) + len) == '=')
			return (*env + len + 1);
		++env;
	}
	return (NULL);
}

int		ft_env_setvalue(char ***env_root, char *key, char *value)
{
	int		len;
	char	**env;
	char	*new_var;

	env = *env_root;
	len = ft_strlen(key);
	new_var = (char *)malloc(sizeof(char) * (len + ft_strlen(value) + 2));
	if (!*env)
		return (0);
	ft_strcpy(new_var, key);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	while (*env)
	{
		if (!ft_strncmp(*env, key, len) && *((*env) + len) == '=')
		{
			free(*env);
			*env = new_var;
			return (1);
		}
		++env;
	}
	*env_root = ft_tabadd(*env_root, new_var);
	free(new_var);
	return (1);
}

int		ft_env_delvalue(char ***env_root, char *key)
{
	int		len;
	char	**env;
	char	**new_env;
	int		i;
	int		j;

	env = *env_root;
	len = ft_strlen(key);
	if (!*env || !(new_env = (char **)malloc(sizeof(char *) * (ft_tabcount(env) + 1))))
		return (0);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!(!ft_strncmp(env[i], key, len) && *(env[i] + len) == '='))
		{	
			new_env[j] = ft_strdup(env[i]);
			++j;
		}
		++i;
	}
	new_env[j] = 0;
	*env_root = new_env;
	ft_tabdel(env);
	return (1);
}
