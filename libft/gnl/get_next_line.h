/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:18:52 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/11/29 18:24:53 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s1);
char	*gnl_strjoin(const char *s1, const char *s2);
size_t	gnl_strlen(const char *s);
char	*gnl_substr(char *str, size_t start, int size);

#endif
