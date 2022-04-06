/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:55:21 by ayakdi            #+#    #+#             */
/*   Updated: 2022/04/02 13:20:31 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_ischarset(char c, char *sep)
{
	int	i;

	i = -1;
	while (sep[++i])
		if (c == sep[i])
			return (1);
	return (0);
}

static int	ft_countwords(char const *str, char *sep)
{
	int	wc;
	int	i;

	i = 0;
	wc = 0;
	while (str[i] && ft_ischarset(str[i], sep))
		i++;
	while (str[i])
	{
		wc++;
		while (str[i] && !ft_ischarset(str[i], sep))
			i++;
		while (str[i] && ft_ischarset(str[i], sep))
			i++;
	}
	return (wc);
}

static char	*ft_dup(char const *str, char *sep)
{
	int		len;
	int		i;
	char	*cpy;

	len = 0;
	i = 0;
	while (str[len] && !ft_ischarset(str[len], sep))
		len++;
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (str[i] && !ft_ischarset(str[i], sep))
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split(char const *s, char *sep)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (ft_countwords(s, sep) + 1));
	if (!split)
		return (NULL);
	while (s[i] && ft_ischarset(s[i], sep))
		i++;
	while (s[i])
	{
		split[j] = ft_dup(&s[i], sep);
		while (s[i] && !ft_ischarset(s[i], sep))
			i++;
		while (s[i] && ft_ischarset(s[i], sep))
			i++;
		j++;
	}
	split[j] = 0;
	return (split);
}
