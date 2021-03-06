/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capitalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:25:44 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:25:45 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		ft_strcapitalize(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str = *str - 32;
		++str;
	}
}
