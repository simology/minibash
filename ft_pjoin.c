#include "minishell.h"

char	**ft_pjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[0][i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[1][i + j] = s2[j];
		j++;
	}
	str[0][i + j] = '\0';
	return (str);
}
