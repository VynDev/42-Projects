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

void	data_free()
{
	t_data	*data;

	data = get_data();
	ft_tabdel(data->env);
	if (data->last_dir)
		free(data->last_dir);
	free(data);
}

void	data_init(char **env)
{
	t_data	*data;

	data = get_data();
	data->env = ft_tabdup(env);
	data->last_dir = NULL;
	data->fork_pid = 0;
}

t_data	*get_data()
{
	static t_data	*data = NULL;

	if (!data)
	{
		data = (t_data *)malloc(sizeof(t_data));
		if (!data)
			return (NULL);
		data->exit_shell = 0;
		data->last_dir = NULL;
	}	
	return (data);
}
