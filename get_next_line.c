/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas < dierojas@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/03/04 19:57:00 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	char		*buff;
	char		*aux;
	static char	*rest;
	char		*gnl;
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
		aux = ft_strjoin(aux, buff);
		if (ft_strchr(buff, '\n'))
		{
			ft_strjoin(rest, buff);
			break;
		}
		readed = read(fd, buff, BUFFER_SIZE);
	}
	free (buff);
	return (aux);
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
