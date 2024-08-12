#include "minishell.h"

void	allocation(char *src, size_t l, char **dst, int type)
{
	if (type == 1 && l == 0)
	{
		while (src[l] && src[l] != '|' && src[l] != ' ' && !check_dir(src[l]))
			l++;
	}
	dst[0] = (char *)malloc((sizeof(char) * l) + 1);
	if (!dst[0])
		write(2, "fail allocatin\n", 15), exit(1);
}

char	*ft_strncpy(char *dst, char *src, int index)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (src[i] && i < (unsigned int)index)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
