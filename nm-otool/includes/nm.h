/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:48:24 by xesnault          #+#    #+#             */
/*   Updated: 2017/01/30 12:37:40 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
# include <stdlib.h>
# include <elf.h>
# include <ar.h>
# include <sys/stat.h>

void			handle_elf(void *ptr);
void			handle_ar(void *ptr, struct stat buf);
void			handle_64bits(Elf64_Ehdr *header);

void			ft_putnstr_c(char *str, int n);
void			ft_putnstr_c2(char *str);
int				ft_strcmp_c(const char *ss1, const char *ss2);

#endif
