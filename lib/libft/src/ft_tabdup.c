#include "libft.h"

char	**ft_tabdup(char **src)
{
	char	**dup;
	int		count;
	int		i;

	if (!src)
		return (NULL);
	count = ft_tablen(src);
	dup = ft_calloc(count + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(src[i]);
		if (!dup[i])
		{
			free_tab(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}
