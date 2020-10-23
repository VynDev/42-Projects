#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	ft_putstr("TEST: ERROR\n");
	char *addr;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
	ft_putstr("TEST: ERROR OK\n");
} 