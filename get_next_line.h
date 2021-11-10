#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h> // malloc
#include <unistd.h>	// read
#include <sys/types.h> // open
#include <sys/stat.h> // open
#include <fcntl.h> // open

char	*get_next_line(int fd);
int		ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
char	*ft_strndup(char *s, int n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);

#endif
