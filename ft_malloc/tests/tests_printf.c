#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>

int				main()
{
	ft_putstr("TEST: FT_PRINTF\n");
	ft_printf("It's just a test!\n");
	ft_printf("This is the number %d\n", 42);
	ft_printf("This is the number %d with another string: \"%s\" and an arbitrary choosen hexadecimal number %x\n", 42, "Just Monika...", 368436583);
	ft_putstr("TEST: FT_PRINTF OK\n");
	return (0);
}