
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*source;
	char	*destination;

	if (!src && !dst)
		return (NULL);
	i = 0;
	source = (char *) src;
	destination = (char *) dst;
	if (src < dst)
		while (len--)
			destination[len] = source[len];
	else
	{
		while (len--)
		{
			destination[i] = source[i];
			i++;
		}
	}
	return (dst);
}
