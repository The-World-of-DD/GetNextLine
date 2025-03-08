/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas <dierojas@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/03/08 14:16:56 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	char		*buff;
	char		*gnl;
	static char	*aux;
	ssize_t		readed;

	aux = ft_strdup("");
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
		aux = ft_strjoin(aux, buff);
		if (ft_strchr(buff, '\n') || EOF)
			break;
		readed = read(fd, buff, BUFFER_SIZE);
	}
	if (!aux)
		return(NULL);
	gnl = ft_extract_line(aux);
	aux = ft_update_aux(aux, gnl);
	free(buff);
	free(aux);
	return(gnl);
}

char	*ft_extract_line(char *aux)//dado el parametro de un string, recorta todo lo que haya antes de un \n
{
	char	*line;
	size_t	y;
	size_t	i;

	if(!aux)
		return (NULL);
	y = 0;
	while (aux[y] && aux[y] != '\n')
		y++;
	line = malloc(y + 2);
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

char	*ft_update_aux(char *aux, char *gnl)
{
	char	*rest;
	size_t	i;
	size_t	k;
	size_t	o;

	if (!aux || !gnl)
		return (NULL);
	i = 0;
	while (aux[i] && aux[i] != '\n')
		i++;
	if (aux[i] == '\n')
		i++;//nos saltamos el coso
	k = ft_strlen(aux);
	rest = malloc(k - i + 1);
	o = 0;
	while (gnl[i])
	{
		rest[o] = aux[i];
		i++;
		o++;
	}
	rest[o] = '\0';
	free(aux);
	return (rest);
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
