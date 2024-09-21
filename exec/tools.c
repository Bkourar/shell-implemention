#include "../prs/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize)
	{
		while (src[i] && (i + 1) < dstsize)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ild;
	size_t	srclen;

	i = 0;
	ild = 0;
	srclen = ft_strlen(src);
	if (!dst && !dstsize)
		return (srclen);
	while (dst[ild] && ild < dstsize)
	{
		ild++;
	}
	while (src[i] && ild + i + 1 < dstsize)
	{
		dst[ild + i] = src[i];
		i++;
	}
	if (ild + i < dstsize)
	{
		dst[ild + i] = '\0';
	}
	return (ild + srclen);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
	{
		return ((char *)(s + i));
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (!n)
	{
		return (0);
	}
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
	{
		i++;
	}
	if (i == n)
	{
		return (0);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	just_cmd(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

char	*exec_join(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	j = 0;
	if (!s1 && !s2)
		return (string = NULL, NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	string = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!string)
		return (free((char *)s2), NULL);
	i = 0;
	while (s1[i])
		string[j++] = s1[i++];
	i = 0;
	while (s2[i])
		string[j++] = s2[i++];
	string[j] = '\0';
	return (string);
}

char	*get_path(char **arr, char *cmd)
{
	int		i;
	char	*pth;
	
	i = 0;
	pth = NULL;
	if (!cmd)
		return (NULL);
	if (just_cmd(cmd) == 0)
	{
		if (access(cmd, X_OK) != -1)
			return(cmd);
		return (NULL);
	}
	while(arr && arr[i])
	{
		pth = exec_join(arr[i], "/");
		pth = exec_join(pth, cmd);
		if (access(pth, X_OK) != -1)
			return (pth);
		i++;
		free(pth);
		pth = NULL;
	}
	free(pth);
	pth = NULL;
	return (NULL);
}
