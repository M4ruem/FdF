
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*string;

	i = 0;
	string = (const char *) s;
	while (n--)
	{
		if (string[i] == (char) c)
			return ((void *) &s[i]);
		i++;
	}
	return (0);
}
