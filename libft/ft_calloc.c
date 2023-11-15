
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (!size && ((SIZE_MAX / size) < count))
		return (NULL);
	arr = malloc(count * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, size * count);
	return (arr);
}
