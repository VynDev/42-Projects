/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:32:57 by xesnault          #+#    #+#             */
/*   Updated: 2016/11/03 11:37:15 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int		find_next_word(char const *s, char c, size_t i)
{
	while (s[i] == c)
	{
		if (s[i] == '"' && ++i)
			while (s[i] && s[i] != '"')
				++i;
		i++;
	}
	return (i);
}

static int		find_end_word(char const *s, char c, size_t i)
{
	while (s[i] != c && s[i])
	{
		if (s[i] == '"' && ++i)
			while (s[i] && s[i] != '"')
				++i;
		i++;
	}	
	return (i);
}

static size_t	get_nb_word(char const *s, char c)
{
	size_t		i;
	size_t		nb_word;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		if (s[i] == '"' && ++i)
			while (s[i] && s[i] != '"')
				++i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			nb_word++;
		i++;
	}
	return (nb_word);
}

static void		free_tab(char **tab, size_t j)
{
	size_t		i;

	i = 0;
	while (i < j)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

char			**ft_strsplit_quote(char const *s, char c)
{
	size_t		i;
	size_t		j;
	size_t		nb_word;
	char		**tab;

	i = 0;
	j = 0;
	nb_word = !s ? 0 : get_nb_word(s, c);
	tab = !s ? 0 : (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (NULL);
	while (j < nb_word)
	{
		i = find_next_word(s, c, i);
		tab[j] = ft_strsub(s, i, find_end_word(s, c, i) - i);
		if (!tab[j])
		{
			free_tab(tab, j);
			return (NULL);
		}
		i = find_end_word(s, c, i);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
