
#include "libft.h"

static int	word_count(char const *str, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			counter++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (counter);
}

static char	*get_word(char const *str, char c, size_t start)
{
	char	*word;
	size_t	i;
	size_t	j;
	size_t	end;

	i = start;
	j = 0;
	end = start;
	while (str[end] != c && str[end])
		end++;
	word = malloc((end - start) + 1);
	if (!word)
		return (NULL);
	while (str[i] != c && str[i])
		word[j++] = str[i++];
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	words = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words[j++] = get_word(s, c, i);
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	words[j] = NULL;
	return (words);
}
