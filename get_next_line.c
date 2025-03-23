/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas < dierojas@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/03/23 22:13:16 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*gnl;
	static char	*aux = NULL;

	if ((BUFFER_SIZE <= 0) || fd < 0)
		return (NULL);
	if (!aux)
		aux = ft_strdup("");
	aux = ft_aux_reading(fd, aux);
	if (!aux || aux[0] == '\0')
		return (free(aux), aux = NULL, NULL);
	gnl = ft_extract_line(aux);
	aux = ft_update_aux(aux);
	return (gnl);
}
char *ft_aux_reading(int fd, char *aux)
{
	char	*buff;
	ssize_t	readed;
	char	*new_aux;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	readed = read(fd, buff, BUFFER_SIZE);
	while (readed > 0)
	{
		buff[readed] = '\0';
		new_aux = ft_strjoin(aux, buff);
		if (!new_aux)
			return (free(buff), free(aux), NULL);
		free(aux);
		aux = new_aux;
		if (ft_strchr(buff, '\n'))
			break;
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
		return (free(aux), NULL);
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
		return (free(aux), NULL);
	rest = malloc(ft_strlen(aux) - i + 1);
	if (!rest)
		return (free(aux), NULL);
	o = 0;
	while (aux[i])
	{
		rest[o] = aux[i];
		i++;
		o++;
	}
	rest[o] = '\0';
	return (free(aux), rest);
}
/*
# include <stdio.h>
int main ()
{
    int fd = open("texto.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return 1;
    }
	char	*line = get_next_line(fd);
	while (line)
	{
		printf("Linea leida --> %s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return 0;
}
*/

TEST("read_error.txt", {
	char *name = "read_error.txt";
	int fd = open(name, O_RDONLY);
	/* 1 */ test_gnl(fd, "aaaaaaaaaa\n");
	/* 2 */ test_gnl(fd, "bbbbbbbbbb\n");
	// set the next read call to return -1
	next_read_error = 1;
	if (BUFFER_SIZE > 100) {
		char *temp;
		do {
			temp = get_next_line(fd);
			free(temp);
		} while (temp != NULL);
	}
	/* 3 */ test_gnl(fd, NULL);
	next_read_error = 0;
	close(fd);
	fd = open(name, O_RDONLY);
	/* 4 */ test_gnl(fd, "aaaaaaaaaa\n");
	/* 5 */ test_gnl(fd, "bbbbbbbbbb\n");
	/* 6 */ test_gnl(fd, "cccccccccc\n");
	/* 7 */ test_gnl(fd, "dddddddddd\n");
	/* 8 */ test_gnl(fd, NULL);
	if (res != 1) {
		fprintf(errors_file, YEL "Probable reason" NC ": You should clear the static buffer when a call to read returns -1\n");
	}
});
