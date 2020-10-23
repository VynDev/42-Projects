#include "libft.h"
#include "ft_irc_server.h"
#include <errno.h>

void				c_exit(int res, int err, char *str)
{
	if (res == err)
	{
		ft_printf("Fatal error: %s => %s\n", str, strerror(errno));
		exit(1);
	}
}

void				cv_exit(void *res, void *err, char *str)
{
	if (res == err)
	{
		ft_printf("Fatal error: %s => %s\n", str, strerror(errno));
		exit(1);
	}
}