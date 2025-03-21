/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas <dierojas@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/03/12 22:25:04 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buff;
	char		*gnl;
	static char	*aux = NULL;
	ssize_t		readed;

	if (!aux)
		aux = ft_strdup("");
	if ((BUFFER_SIZE <= 0) || fd < 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	readed = read(fd, buff, BUFFER_SIZE);
	if (readed < 0)
		return (free(buff), NULL);
	while (readed > 0)
	{
		buff[readed] = '\0';
		char	*new_aux = ft_strjoin(aux, buff);
		free(aux);
		aux = new_aux;
		//aux = ft_strjoin(aux, buff);
		if (ft_strchr(buff, '\n'))
			break;
		readed = read(fd, buff, BUFFER_SIZE);
	}
	if (!aux || aux[0] == '\0')
		return(free (buff), free(aux), aux = NULL, NULL);
	gnl = ft_extract_line(aux);
	aux = ft_update_aux(aux);
	return(free(buff), gnl);
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
		i++;//nos saltamos el coso en caso de que sea \n
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
	while (line)
	{
		printf("Linea leida --> %s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return 0;
}

