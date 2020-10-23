#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>

#define M (1024 * 1024)

void			print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr1;
	char *addr2;
	char *addr3;

	ft_putstr("TEST: REALLOC3\n");
	addr1 = (char*)malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = (char*)malloc(16*M);
	(void)addr2;
	addr3 = (char*)realloc(addr1, 128*M);
	addr3[127*M] = 42;
	print(addr3);
	ft_putstr("TEST: REALLOC3 OK\n");
	return (0);
} 