#include "libft.h"

void			ft_putnstr_c(char *str, int n)
{
	while (n != 0 && *str != '/')
	{
		ft_putchar(*str);
		--n;
		++str;
	}
	ft_putstr(":\n");
}

void			ft_putnstr_c2(char *str)
{
	while (*str != '/')
	{
		ft_putchar(*str);
		++str;
	}
	ft_putstr(":\n");
}