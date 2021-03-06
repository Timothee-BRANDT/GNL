/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:09:26 by tbrandt           #+#    #+#             */
/*   Updated: 2021/11/11 15:51:03 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	push_buffer(char **str, char **buffer, char **tmp)
{
	*tmp = ft_strjoin(*str, *buffer);
	free(*str);
	*str = ft_strdup(*tmp);
	free(*tmp);
}

void	is_excess(char **str, char **excess)
{
	*str = ft_strjoin(*str, *excess);
	free(*excess);
	*excess = 0;
}

// second free if empty file
char	*return_line(char **excess, char *str, char *tmp, int read_value)
{
	if (read_value <= 0 && str[0] != 0)
		return (str);
	if (ft_strchr(str, '\n') >= 0)
	{
		tmp = ft_strndup(str, ft_strchr(str, '\n'));
		*excess = ft_strdup(str + (ft_strchr(str, '\n') + 1));
		free(str);
		return (tmp);
	}
	free(str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*excess;
	char		*buffer;
	char		*str;
	char		*tmp;
	int			read_value;

	str = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	read_value = 1;
	is_excess(&str, &excess);
	while ((read_value > 0) && ft_strchr(str, '\n') < 0)
	{
		read_value = read(fd, buffer, BUFFER_SIZE);
		buffer[read_value] = '\0';
		push_buffer(&str, &buffer, &tmp);
	}
	free(buffer);
	str = return_line(&excess, str, tmp, read_value);
	return (str);
}
/*
int main(int argc, char *argv[])
{
	int	fd;
	char	*line;

	if (!argc)
		return (1);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line != '\0') 
	{
		printf("GNL return : %s\n", line);
		line = get_next_line(fd);
		free(line);
	}
	return (0);
}*/
