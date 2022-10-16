#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (len > 0 && start <= ft_strlen(s))
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	return (str);
}
