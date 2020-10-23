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

int		file_check_access(char *file)
{
	if (!access(file, X_OK))
		return (1);
	return (0);
}

int		file_check(char *file, char *command)
{
	char	error;
	DIR		*dir;

	error = 0;
	if (!command)
		return (0);
	else if (!file && (error = 1))
		print_error(command, ": command not found");
	else if (!file_check_access(file) && (error = 1))
		print_error("Permision denied", NULL);
	else if ((dir = opendir(file)) && (error = 1) && !closedir(dir))
		print_error(command, ": is a directory");
	return (error ? 0 : 1);
}
