#include <unistd.h>
#include "libft.h"

int main()
{
	ft_putstr("TEST: FREE2\n");
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	ft_putstr("TEST: FREE2 OK\n");
	return (0);
} 