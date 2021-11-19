/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:18:24 by oakoudad          #+#    #+#             */
/*   Updated: 2021/11/18 15:52:28 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *r, int fd)
{
	char	*buffer;
	int		a;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	a = 1;
	while (a > 0 && ft_strchr(r, '\n') == NULL)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a == 0)
			break ;
		if (a == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[a] = '\0';
		r = ft_strjoin(r, buffer);
	}
	free(buffer);
	return (r);
}

char	*ft_affiche_line(char *r)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (*r == '\0')
		return (NULL);
	while (r[i] && r[i] != '\n')
		i++;
	if (r[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = r[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_re(char *r)
{
	char	*p;
	int		start;
	int		j;

	start = 0;
	while (r[start] && r[start] != '\n')
		start++;
	if (r[start] == '\n')
		start++;
	if (r[start] == '\0')
	{
		free(r);
		return (NULL);
	}
	p = (char *)malloc(sizeof(char) * (ft_strlen(r) - start + 1));
	if (!p)
		return (NULL);
	j = 0;
	while (r[start])
		p[j++] = r[start++];
	p[j] = '\0';
	free(r);
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*r;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	r = get_line(r, fd);
	if (!r)
		return (NULL);
	line = ft_affiche_line(r);
	r = ft_re(r);
	return (line);
}
#include <stdio.h>
int main()
{

	int fd = open("txt.txt", O_RDONLY);

	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	//printf("%%s");
}
