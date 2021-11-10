/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:09:26 by tbrandt           #+#    #+#             */
/*   Updated: 2021/11/10 17:27:22 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	push_line(char **str, char **buffer, char **tmp)
{
	*tmp = ft_strjoin(*str, *buffer);
	free(*str);
	*str = ft_strdup(*tmp);
	free(*tmp);
}

void	check_excess(char **str, char **excess)
{
	if (excess)
	{
		*str = ft_strjoin(*str, *excess);
		free(*excess);
		*excess = 0;
	}
}

char	*return_line(char **excess, char *str, char *tmp, int read_value)
{
	if (read_value < 0)
		return (str);
	else if (ft_strchr(str, '\n') >= 0)
	{
		*excess = ft_strdup(str + ft_strchr(str, '\n') + 1);
		tmp = ft_strndup(str, ft_strchr(str, '\n'));
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
	excess = NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || read(fd, buffer, 0) < 0)
	{
		free(buffer);
		free(str);
		return (NULL);
	}
	check_excess(&str, &excess);
	read_value = 1;
	while ((ft_strchr(str, '\n') < 0) && (read_value != 0))
	{
		read_value = read(fd, buffer, BUFFER_SIZE);
		buffer[read_value] = '\0';
		push_line(&str, &buffer, &tmp);
	}
	free(buffer);
	return (return_line(&excess, str, tmp, read_value));
}

int main(int argc, char *argv[])
{
	int	fd;
	char	*line;
	int	i;

	if (!argc)
		return (1);
	fd = open(argv[1], O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line) // tant que line n'est pas egal a NULL
	{
		printf("GNL return : %s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
