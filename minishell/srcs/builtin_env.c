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

void			builtin_env(int ac, char **av)
{
	t_data	*data;
	char	**env;

	(void)ac;(void)av;
	data = get_data();
	env = data->env;
	while (*env)
	{
		ft_printf("%s\n", *env);
		++env;
	}
}
