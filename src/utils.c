#include "../includes/game.h"

char	*ft_strdupn(const char *str1)
{
	int		i;
	char	*dupstr;
	int		len;

	len = ft_strlen((char *)str1);
	dupstr = malloc((len + 1) * sizeof(char));
	if (dupstr == NULL)
		return (NULL);
	i = 0;
	while (str1[i] != '\0' && str1[i] != '\n')
	{
		dupstr[i] = str1[i];
		i++;
	}
	dupstr[i] = '\0';
	return (dupstr);
}

int	ft_max_width(char **map)
{
	int		i;
	size_t	max;

	i = -1;
	max = 0;
	while (map[++i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
	}
	return (max);
}
