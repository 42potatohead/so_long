/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:17:28 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/11/29 17:12:54 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	free_fd(char *string)
{
	if(string)
	{
		free(string);
		string = NULL;
	}
}

static char	*readline(int fd, char *buf, char **string)
{
	int		i;
	char	*tmp;
	// static int x;

	// x++;
	i = 1;
	while (i > 0)
	{
		// if (x == 2)
		// 	i = -1;
		// else
			i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
			return (free (buf), NULL);
		if (i == 0)
			break ;
		buf[i] = '\0';
		tmp = *string;
		if (*string)
			*string = gnl_strjoin(*string, buf);
		else
			*string = gnl_strdup(buf);
		free(tmp);
		if (*string != NULL)
			if (gnl_strchr(*string, '\n'))
				break ;
	}
	free(buf);
	return (*string);
}

static char	*extract(char *string)
{
	int	i;

	i = 0;
	if (!string || string[0] == '\0')
		return (NULL);
	while (string[i] != '\0')
	{
		if (string[i] == '\n')
			return (gnl_substr(string, 0, i + 1));
		i++;
	}
	return (gnl_strdup(string));
}

char	*get_next_line(int fd)
{
	static char	*string;
	char		*buff;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = NULL;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	// printf("before buff check %s \n", buff);
	if (buff == NULL)
	{
		free_fd(string);
		return (NULL);
	}
	// printf("after buff check %s \n", buff);
	buff[0] = '\0';
	line = NULL;
	if (!readline(fd, buff, &string) || !string)
		return (string = NULL, NULL);
	// printf("test: %s \n", string);
	line = extract(string);
	temp = string;
	if (line)
		string = gnl_substr(string, gnl_strlen(line), gnl_strlen(string)
				- gnl_strlen(line));
	else
		string = NULL;
	free(temp);
	return (line);
}
