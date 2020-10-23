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
//#include <term.h>

void	term_init()
{
	struct termios	termios_p;
	char			*name_term;
	t_data			*data;

	data = get_data();
	if ((name_term = getenv("TERM")) == NULL)
		ft_printf("ERROR 0\n");
	if (tgetent(NULL, name_term) < 1)
		ft_printf("ERROR 1\n");

	tcgetattr(0, &termios_p);
	data->termios_backup = termios_p;
 	termios_p.c_lflag &= ~(ICANON);
	termios_p.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, &termios_p);
}

void	term_reset()
{
	 char			*name_term;
	 t_data			*data;

	data = get_data();
	if ((name_term = getenv("TERM")) == NULL)
		ft_printf("ERROR 0\n");
	if (tgetent(NULL, name_term) < 1)
		ft_printf("ERROR 1\n");

	tcsetattr(0, TCSANOW, &data->termios_backup);
}
