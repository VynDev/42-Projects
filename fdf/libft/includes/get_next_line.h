/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:02:46 by xesnault          #+#    #+#             */
/*   Updated: 2016/12/06 14:10:39 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 8096

typedef struct	s_file
{
	char		buffer[BUFF_SIZE];
	int			fd;
	int			pos;
	int			ret;
}				t_file;

#endif
