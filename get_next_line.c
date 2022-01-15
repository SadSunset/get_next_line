/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:24:14 by fbinary           #+#    #+#             */
/*   Updated: 2022/01/13 21:58:25 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + len);
	while (i < len)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

static void	check_leaks(char **box, char *bag)
{
	char	*temp;

	if (!*box)
		*box = ft_strdup(bag);
	else
	{
		temp = ft_strjoin(*box, bag);
		if (box != NULL)
			free(*box);
		*box = temp;
	}
}

static void	word(char *n, char **box)
{
	char	*beg;

	beg = NULL;
	if (ft_strlen(n + 1) > 0)
	{
		beg = ft_strdup(n + 1);
		if (box != NULL)
			free(*box);
		*box = ft_strdup(beg);
		free(beg);
		beg = NULL;
	}
	else
	{
		if (*box)
		{
			if (box != NULL)
				free(*box);
			*box = NULL;
			box = NULL;
		}
	}
}

static char	*find_n_and_write_line(char **box, char **line)
{
	char	*n;

	n = ft_strchr(*box, '\n');
	if (n == NULL)
		*line = ft_substr(*box, 0, ft_strlen(*box));
	else
		*line = ft_substr(*box, 0, (ft_strlen(*box) - ft_strlen(n) + 1));
	if (n != NULL)
		word(n, box);
	else
	{
		if (box != NULL)
			free(*box);
		*box = NULL;
		box = NULL;
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*box[1024];
	char		bag[BUFF_SIZE + 1];
	long		result_op;
	char		*line;

	line = NULL;
	if (fd < 0 || fd > 1024 || (read(fd, box[fd], 0) < 0))
		return (NULL);
	if (box[fd] && (ft_strchr(box[fd], '\n') != NULL))
	{
		find_n_and_write_line(&box[fd], &line);
		return (line);
	}
	result_op = read(fd, bag, BUFF_SIZE);
	while (result_op > 0)
	{
		bag[result_op] = '\0';
		check_leaks(&box[fd], bag);
		if (ft_strchr(box[fd], '\n') != NULL)
			break ;
		result_op = read(fd, bag, BUFF_SIZE);
	}
	if (result_op < BUFF_SIZE && !box[fd])
		return (NULL);
	return (find_n_and_write_line(&box[fd], &line));
}
