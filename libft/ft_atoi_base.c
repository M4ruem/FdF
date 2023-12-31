
#include "libft.h"

static int	isvalid(char c, char *base)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(base))
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	value_of(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int	ft_atoi_base(const char *str, char *base)
{
	int	result;
	int	sign;

	result = 0;
	while (*str == ' ')
		str++;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (isvalid(*str, base))
		result = result * ft_strlen(base) + value_of(*str++);
	return (result * sign);
}
