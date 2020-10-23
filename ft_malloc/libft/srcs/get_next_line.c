/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:53:22 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/17 15:17:47 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"

static int		delete_fd(t_list **root, const int fd, int r_value, char *line)
{
	t_list	*before;
	t_list	*current;

	if (line)
		free(line);
	before = NULL;
	current = *root;
	while (current)
	{
		if (((t_file *)current->content)->fd == fd)
		{
			free(current->content);
			if (before)
				before->next = current->next;
			else
				*root = current->next;
			free(current);
			return (r_value);
		}
		before = current;
		current = current->next;
	}
	return (r_value);
}

static int		fill_line(t_file *file, char **line)
{
	int		base_pos;
	char	*temp;

	temp = *line;
	base_pos = file->pos;
	while (file->pos < file->ret && file->buffer[file->pos] != '\n')
		file->pos = file->pos + 1;
	*line = (char *)malloc(sizeof(char)
			* ((ft_strlen(temp) + (file->pos - base_pos))) + 1);
	if (!*line)
		return (0);
	ft_strcpy(*line, temp);
	free(temp);
	ft_strncat(*line, (file->buffer) + base_pos, (file->pos - base_pos));
	if (file->pos == file->ret)
		return (1);
	if (file->buffer[file->pos] == '\n')
		file->pos = file->pos + 1;
	return (0);
}

static int		read_line(t_list **root, t_file *file, char **line)
{
	if (file->pos == -1)
	{
		file->ret = read(file->fd, file->buffer, BUFF_SIZE);
		file->pos = 0;
		if (file->ret <= 0)
			return (delete_fd(root, file->fd, file->ret, *line));
	}
	while (fill_line(file, line) == 1)
	{
		file->ret = read(file->fd, file->buffer, BUFF_SIZE);
		file->pos = 0;
		if (file->ret == 0)
			return (delete_fd(root, file->fd, 1, NULL));
		if (file->ret < 0)
			return (delete_fd(root, file->fd, file->ret, NULL));
	}
	if (file->pos == file->ret)
	{
		file->ret = 0;
		if (file->fd != 0)
			file->ret = read(file->fd, file->buffer, BUFF_SIZE);
		file->pos = 0;
		file->ret <= 0 ? delete_fd(root, file->fd, 1, NULL) : (0);
	}
	return (*line == NULL ? (-1) : (1));
}

static t_list	*find_fd(t_list **list_fd, const int fd)
{
	t_list	*maillon;
	t_file	*file;

	maillon = *list_fd;
	while (maillon)
	{
		if (((t_file *)maillon->content)->fd == fd)
			return (maillon);
		maillon = maillon->next;
	}
	if ((file = (t_file *)malloc(sizeof(t_file))) == NULL)
		return (0);
	file->fd = fd;
	file->pos = -1;
	maillon = ft_lstnew(file, sizeof(t_file));
	free(file);
	if (!maillon)
		return (0);
	ft_lstadd(list_fd, maillon);
	return (maillon);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*list_fd;
	t_list			*maillon;

	if (fd == -1 || !line)
		return (-1);
	*line = ft_strnew(1);
	if ((maillon = find_fd(&list_fd, fd)) != 0)
		return (read_line(&list_fd, maillon->content, line));
	if (*line)
		free(*line);
	return (-1);
}
