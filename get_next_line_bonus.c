/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas < dierojas@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/04/14 14:23:28 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*gnl;
	static char	*aux[MAX_FD];

	if ((BUFFER_SIZE <= 0) || fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (!aux[fd])
		aux[fd] = ft_strdup("");
	aux[fd] = ft_aux_reading(fd, aux[fd]);
	if (!aux[fd] || aux[fd][0] == '\0')
		return (free(aux[fd]), aux[fd] = NULL, NULL);
	gnl = ft_extract_line(aux[fd]);
	aux[fd] = ft_update_aux(aux[fd]);
	return (gnl);
}

char	*ft_aux_reading(int fd, char *aux)
{
	char	*buff;
	ssize_t	readed;
	char	*new_aux;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	readed = read(fd, buff, BUFFER_SIZE);
	if (readed < 0)
		return (free(buff), free(aux), aux = NULL, NULL);
	while (readed > 0)
	{
		buff[readed] = '\0';
		new_aux = ft_strjoin(aux, buff);
		if (!new_aux)
			return (free(buff), free(aux), NULL);
		free(aux);
		aux = new_aux;
		if (ft_strchr(buff, '\n'))
			break ;
		readed = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (aux);
}

char	*ft_extract_line(char *aux)
{
	char	*line;
	size_t	y;
	size_t	i;

	if (!aux)
		return (NULL);
	y = 0;
	while (aux[y] && aux[y] != '\n')
		y++;
	if (aux[y] == '\n')
		y++;
	line = malloc(y + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < y)
	{
		line[i] = aux[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_update_aux(char *aux)
{
	char	*rest;
	size_t	i;
	size_t	o;

	if (!aux)
		return (NULL);
	i = 0;
	while (aux[i] && aux[i] != '\n')
		i++;
	if (aux[i] == '\n')
		i++;
	if (i >= ft_strlen(aux))
		return (NULL);
	rest = malloc(ft_strlen(aux) - i + 1);
	if (!rest)
		return (NULL);
	o = 0;
	while (aux[i])
	{
		rest[o] = aux[i];
		i++;
		o++;
	}
	rest[o] = '\0';
	return (rest);
}
/* 
# include <stdio.h>
int main ()
{
    int fd1 = open("texto.txt", O_RDONLY);
	int fd2 = open("texto2.txt", O_RDONLY);
    if (fd1 < 0 || fd2 < 0)
    {
        perror("Error al abrir el archivo");
        return 1;
    }
	char	*line = get_next_line(fd1);
	char	*line2 = get_next_line(fd2);
	while (line)
	{
		printf("Linea leida --> %s", line);
		free(line);
		line = get_next_line(fd1);
	}
	while (line2)
	{
		printf("Linea leida --> %s", line2);
		free(line2);
		line2 = get_next_line(fd2);
	}
	close(fd1);
	close(fd2);
	return 0;
} */
