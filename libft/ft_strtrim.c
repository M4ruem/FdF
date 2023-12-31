
#include "libft.h"

static int	check_char(char const c, char const *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && check_char(s1[start], set))
		start++;
	while (end > start && check_char(s1[end - 1], set))
		end--;
	arr = malloc(sizeof(*s1) * (end - start + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (start < end)
		arr[i++] = s1[start++];
	arr[i] = '\0';
	return (arr);
}
