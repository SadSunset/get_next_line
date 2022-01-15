/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:35:05 by fbinary           #+#    #+#             */
/*   Updated: 2022/01/13 21:26:50 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 42

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*ft_substr(char *s, int start, int len);
int		ft_strlen(char *s);
void	*ft_memcpy(void *dst, void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);
char	*get_next_line(const int fd);

#endif