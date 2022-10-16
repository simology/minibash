#include "minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	counter;

	counter = 0;
	while (dest[counter] != '\0' )
	{
		counter++;
	}
	while (*src != '\0')
	{
		dest[counter] = *src;
		src++;
		counter++;
	}
	dest[counter] = '\0';
	return (dest);
}