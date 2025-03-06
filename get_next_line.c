/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas < dierojas@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/03/06 10:55:23 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	char		*buff;
	char		*gnl;
	static char	*aux;
	ssize_t		readed;

	aux = NULL;
	if ((BUFFER_SIZE <= 0) || fd < 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	readed = read(fd, buff, BUFFER_SIZE);
	if (readed <= -1)
		return (free(buff), NULL);
	//buffer read process and aux fill//
	while (readed > 0)
	{
		if (ft_strchr(buff, '\n'))
		{
			aux = ft_strjoin(aux, buff);
			break;
		}
		readed = read(fd, buff, BUFFER_SIZE);
	}
	if (!aux)
		return(NULL);
	gnl = ft_ext_line(aux);
	aux = ft_update_aux();
	free(buff);
	return(gnl);
}
/* char	*ft_strim_gnl(char *aux, char *rest)
{
	char	*gnl;
	size_t	len;
	size_t	end;
	size_t	start;

	if (!aux || !aux && !rest)
		return (NULL);
	start = 0;
	while (aux[start])
	{
	
	}
	return (gnl);
}
char	*ft_nullinc_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;

	if (!s1)
	{
		if(s2)
			return (ft_strdup(s2));
		else
			return (ft_strdup(""));
	}
	if (!s2)
		return (ft_strdup(s1));
	s3 = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	s3 = ft_strjoin(ft_strdup(""), (const char *)s1);
	s3 = ft_strjoin(s3, s2);
	i = ft_strlen(s1) + ft_strlen(s2);
	s3[i] = '\0';
	return ((char *)s3);
}

int main ()
{
    int fd = open("texto.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return 1;
    }
	char	*line = get_next_line(fd);
	if (line)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
} 
 */
