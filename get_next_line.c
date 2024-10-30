/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ombatkam <ombatkam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:30:48 by ombatkam          #+#    #+#             */
/*   Updated: 2024/10/29 16:50:59 by ombatkam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_free(char *str)
{
	free (str);
	return (NULL);
}

static char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char)c)
	{
		if (!*s++)
			return (0);
	}
	return ((char *)s);
}

static char	*ft_read(int fd, char *str)
{
	ssize_t	len;
	char	temp[BUFFER_SIZE + 1];
	char	*new_str;

	while (!ft_strchr(str, '\n'))
	{
		len = read(fd, temp, BUFFER_SIZE);
		if (len <= 0)
		{
			if (len == 0 && *str)
				return (str);
			else
			{
				free(str);
				return (NULL);
			}
		}
		temp[len] = '\0';
		new_str = ft_strjoin(str, temp);
		free(str);
		str = new_str;
		if (!str)
			return (NULL);
	}
	return (str);
}

static void	ft_initialisation(char *str, int n)
{
	int	i;

	i = 0;
	while (str[n + i])
	{
		str[i] = str[n + i];
		i++;
	}
	str[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*str;
	int			n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (ft_free(buffer));
		buffer[0] = '\0';
	}
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (ft_free(buffer));
	n = ft_end_line(buffer);
	str = ft_strndup(buffer, n);
	ft_initialisation(buffer, n);
	if (!*buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (str);
}

// #include <stdio.h>
// #include <fcntl.h>
// #include "get_next_line.h"

// int main(int argc, char **argv)
// {
//     int fd;
// 	//char *line;

//     if (argc < 2)
//     {
//         fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
//         return 1;
//     }

//     fd = open(argv[1], O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Erreur à l'ouverture du fichier");
//         return 1;
//     }
// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
//     // 	printf("%s", line);  
//     // 	free(line);        
// 	// }	
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));

//     close(fd);
//     return 0;
// }