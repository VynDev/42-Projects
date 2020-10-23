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
#include <term.h>

static int	my_outc(int c)
{
	write(1, &c, 1);
	return (0);
}

static void	extend_buffer(t_command *cmd)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (cmd->buffer_size + BUFFER_SIZE_CMD))))
		ft_printf("extend buffer malloc failed\n");
	ft_strcpy(tmp, cmd->line);
	free(cmd->line);
	cmd->line = tmp;
	cmd->buffer_size += BUFFER_SIZE_CMD;
}

static void	del_char(t_command *cmd)
{
	char	*res;

	if ((res = tgetstr("le", NULL)) == NULL)
    	ft_printf("ERROR le\n");
    tputs(res, 0, &my_outc);
    if ((res = tgetstr("dc", NULL)) == NULL)
    	ft_printf("ERROR dc\n");
    tputs(res, 0, &my_outc);
    *(cmd->line + (ft_strlen(cmd->line) - 1)) = 0;
    --(cmd->cursor);
}

static void	add_char(t_command *cmd, char *c)
{
	if (cmd->cursor + 1 == cmd->buffer_size)
		extend_buffer(cmd);
	ft_strncat(cmd->line, c, 1);
	ft_putchar(*c);
	++(cmd->cursor);
}

int			get_input(int fd, char **line)
{
	char		buf[3];
	int			ret;
	t_command	cmd;

	if (!(cmd.line = (char *)malloc(sizeof(char) * BUFFER_SIZE_CMD)))
		ft_printf("get input malloc failed\n");
	cmd.buffer_size = BUFFER_SIZE_CMD;
	cmd.cursor = 0;
	*(cmd.line) = 0;
	bzero(buf, 3);
	while ((ret = read(fd, buf, 3)))
	{
		if (ret == 1 && buf[0] >= 32 && buf[0] < 127)
			add_char(&cmd, buf);
		else if (ret == 1 && buf[0] == 127 && ft_strlen(cmd.line) > 0)
			del_char(&cmd);
		else if (ret == 1 && buf[0] == 10)
			break;
	}
	*line = cmd.line;
	ft_putchar('\n');
	return (0);
}
