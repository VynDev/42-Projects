#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>

#define M (1024 * 1024)

void			print(char *s)
{
	write(1, s, strlen(s));
}

int				main()
{
	ft_putstr("TEST: REALLOC2\n");
	char	*addr1;
	char	*addr3;

	addr1 = (char *)malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char *)realloc(addr1, 128*M);
	addr3[127*M] = 42;
	print(addr3);
	ft_putstr("TEST: REALLOC2 OK\n");
	return (0);
}