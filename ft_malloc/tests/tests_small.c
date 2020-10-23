#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>

int				main()
{
	ft_putstr("TEST: SMALL 2048\n");
	char *str;
	int i = 0;
	while (i < 1024)
	{
		str = (char *)malloc(2048);
		str[0] = 42;
		++i;
	}
	ft_putstr("TEST: SMALL 2048 OK\n");
	return (0);
}