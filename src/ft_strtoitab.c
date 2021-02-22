#include "../inc/cub3D.h"

int		*tab_atoi(char **alnum)
{
	int		*tab;
	int		i;

	i = 0;
	while (alnum[i])
		i++;
	tab = ft_calloc(i, sizeof(tab));
	while (i--)
		tab[i] = ft_atoi(alnum[i]);
	return (tab);
}

int		*ft_strtoitab(char *str)
{
	char	**split;
	int		*tab;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ',' || str[i] == ' ')
		{
			if ((split = ft_splitset(str, " ,")) == NULL)
				return (NULL);
			else
			{
				tab = tab_atoi(split);
				ft_freetab(split);
				return (tab);
			}
		}
	}
	if ((tab = ft_calloc(i, sizeof(tab))) == NULL)
		return (NULL);
	while (i--)
		tab[i] = ft_isdigit(str[i]) ? (int)(str[i] - '0') : (int)str[i];
	return (tab);
}