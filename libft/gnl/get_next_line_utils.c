/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:17:24 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/22 14:43:17 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}

char	*gnl_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + 1));
	if (!str)
	{
		str = NULL;
		free(str);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*gnl_substr(char *str, size_t start, int size)
{
	char	*new_str;
	int		len;
	int		i;

	if (size == 0)
		return (NULL);
	if (str == NULL)
		return (NULL);
	if (start > gnl_strlen(str))
		return (gnl_strdup(""));
	len = gnl_strlen(&str[start]);
	if (len < size)
		size = len;
	new_str = malloc((size + 1) * sizeof(char));
	if (!new_str)
		return (new_str = NULL, free(new_str), NULL);
	i = 0;
	while (i < size)
	{
		new_str[i] = str[start];
		start++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*gnl_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!res)
		return (res = NULL, free(res), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		res[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		res[j] = s2[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
