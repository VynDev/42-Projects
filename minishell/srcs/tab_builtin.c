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

t_tab_builtin	*get_tab_builtin()
{
	static	t_tab_builtin	tab_builtin[7] = 
	{
		{"exit", &builtin_exit},
		{"cd", &builtin_cd},
		{"env", &builtin_env},
		{"setenv", &builtin_setenv},
		{"unsetenv", &builtin_unsetenv},
		{"echo", &builtin_echo},
		{NULL, NULL}
	};

	return (tab_builtin);
}