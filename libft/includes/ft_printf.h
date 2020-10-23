/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:51:52 by xesnault          #+#    #+#             */
/*   Updated: 2016/12/06 14:11:58 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define CCR const char *restrict
# include <stdarg.h>
# include <stdlib.h>

typedef struct		s_pcursor
{
	int				last;
	int				i;
}					t_pcursor;

typedef struct		s_convert
{
	char			flag[5];
	int				width;
	int				precision;
	char			length[2];
	char			specifier;
}					t_convert;

typedef struct		s_rep
{
	char			*text;
	size_t			len;
}					t_rep;

char				*add_to_str(char *str, char *add);

void				reset_convert(t_convert *convert);

void				fill_convert(t_convert *convert,
	CCR format, t_pcursor *cur, va_list *ap);

int					isspecifier(CCR format, int i);

int					isflag(CCR format, int i);

int					islength(CCR format, int i);

void				set_flag(t_convert *convert, char flag);

void				set_length(t_convert *convert, char length);

void				set_precision(t_convert *convert,
	CCR format, t_pcursor *cur, va_list *ap);

void				set_width(t_convert *convert,
	CCR format, t_pcursor *cur, va_list *ap);

t_rep				*convert_di(t_convert *convert, va_list *ap);

t_rep				*convert_o(t_convert *convert, va_list *ap);

t_rep				*convert_u(t_convert *convert, va_list *ap);

t_rep				*convert_x(t_convert *convert, va_list *ap);

t_rep				*convert_s(t_convert *convert, va_list *ap);

t_rep				*convert_c(t_convert *convert, va_list *ap);

t_rep				*convert_p(t_convert *convert, va_list *ap);

t_rep				*convert_b(t_convert *convert, va_list *ap);

t_rep				*convert_cmaj(t_convert *convert, va_list *ap);

t_rep				*convert_smaj(t_convert *convert, va_list *ap);

char				*add_precision(char *str, int precision);

char				*add_width(char *number, int width, int direction);

char				*abs_char(char *number);

int					flag_exist(t_convert *convert, char flag);

char				*add_sign(char *number);

char				*pad_zero(char *number, int nb_zero);

char				*add_prefix(char *number, t_convert *convert);

t_rep				*create_rep(char *text, size_t len);

t_rep				*convert_add_pourcent(t_convert *convert);

t_rep				*convert_bad_spec(t_convert *convert);

char				*preconvert_atoi_base(t_convert *convert,
	va_list *ap, int *w);

void				add_color(CCR format, t_pcursor *cur, int *len, char **str);

int					add_to_finalstr(char **str,
	char *add, int str_len, int add_len);

#endif
