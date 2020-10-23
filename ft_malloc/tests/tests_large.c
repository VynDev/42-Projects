#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>

int				main()
{
	ft_putstr("TEST: LARGE 5000 to 10000\n");
	char *str;
	int i = 5000;
	while (i < 10000)
	{
		str = (char *)malloc(i);
		str[0] = 42;
		++i;
	}
	ft_putstr("TEST: LARGE 5000 to 10000 OK\n");
	return (0);
}