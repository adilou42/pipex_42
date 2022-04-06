/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:56:16 by ayakdi            #+#    #+#             */
/*   Updated: 2022/04/02 13:20:13 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			idx;
	int			idx_join;
	char		*join;

	join = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!s1 || !s2 || !join)
		return (NULL);
	idx = 0;
	idx_join = 0;
	while (s1[idx])
		join[idx_join++] = s1[idx++];
	idx = 0;
	while (s2[idx])
		join[idx_join++] = s2[idx++];
	join[idx_join] = '\0';
	return (join);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!needle[j])
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && (i + j < len) && needle[j]
			&& haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

int	permission_error(char *filename)
{
	write(2, "pipex: ", 7);
	write(2, "permission denied: ", 19);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
	return (-1);
}

int	openfile(char *filename, int mode)
{
	if (mode == 0)
	{
		if (access(filename, F_OK) == -1)
		{
			write(2, "pipex: ", 7);
			write(2, "No such file or directory: ", 28);
			write(2, filename, ft_strlen(filename));
			write(2, "\n", 1);
			return (-1);
		}
		else if (access(filename, R_OK) == -1)
			return (permission_error(filename));
		return (open(filename, O_RDONLY));
	}
	else
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) == -1)
			return (permission_error(filename));
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	}
}
