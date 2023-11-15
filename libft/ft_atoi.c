
#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	pos;
	int	num;

	pos = 0;
	num = 0;
	sign = 1;
	while (str[pos] && (str[pos] == '\n' || str[pos] == ' ' || str[pos] == '\t' \
			|| str[pos] == '\r' || str[pos] == '\v' || str[pos] == '\f'))
		pos++;
	if (str[pos] == '-')
	{
		sign = -1;
		pos++;
	}
	else if (str[pos] == '+')
		pos++;
	while (str[pos] >= '0' && str[pos] <= '9')
		num = num * 10 + (str[pos++] - 48);
	return (num * sign);
}
