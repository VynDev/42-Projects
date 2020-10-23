#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>

int				main(void)
{
	ft_putstr("TEST: TINY 1024\n");
	char *str;
	int i = 0;
	while (i < 1024)
	{
		str = (char *)malloc(1024);
		str[0] = 42;
		++i;
	}
	ft_putstr("TEST: TINY 1024 OK\n");
	return (0);
}
