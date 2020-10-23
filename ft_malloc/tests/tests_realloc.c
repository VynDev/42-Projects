#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>

int				main()
{
	ft_putstr("TEST: REALLOC\n");
	char *str;
	(void)str;
	str = (char *)malloc(5000);
	str = realloc(str, 4000);
	ft_putstr("TEST: REALLOC OK\n");
	return (0);
}