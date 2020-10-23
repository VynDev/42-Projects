#include "libft.h"
#include "ft_irc_server.h"

t_cbuffer		*cbuf_create(int size)
{
	t_cbuffer	*cbuf;

	cbuf = (t_cbuffer *)malloc(sizeof(t_cbuffer));
	cbuf->buf = (char *)malloc(sizeof(char) * size);
	cbuf->size = size;
	cbuf->len = 0;
	cbuf->r_cur = 0;
	cbuf->w_cur = 0;
	return (cbuf);
}

int				cbuf_append(t_cbuffer *cbuf, char *str, int len)
{
	int			i;

	i = 0;
	while (i != len && cbuf->len != cbuf->size)
	{
		cbuf->buf[cbuf->w_cur] = str[i];
		++cbuf->len;
		++i;
		++(cbuf->w_cur);
		if (cbuf->w_cur == cbuf->size)
			cbuf->w_cur = 0;
	}
	return (i);
}

int				cbuf_nread(t_cbuffer *cbuf, int n, char *str)
{
	int			i;

	i = 0;
	while (i != n && cbuf->len != 0)
	{
		str[i] = cbuf->buf[cbuf->r_cur];
		++(cbuf->r_cur);
		++i;
		--cbuf->len;
		if (cbuf->r_cur == cbuf->size)
			cbuf->r_cur = 0;
	}
	return (i);
}