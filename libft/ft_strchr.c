
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char) c)
			return (i + (char *) s);
		i++;
	}
	if (s[i] == (char) c)
		return (i + (char *) s);
	return (NULL);
}
