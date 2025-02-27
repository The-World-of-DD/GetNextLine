/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas < dierojas@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/02/26 20:50:42 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	static char	*buff;
	char		*aux;
	char		*rest;
	char		*gnl;
	ssize_t		readed;

	buff = NULL;
	aux = NULL;
	rest = NULL;
	gnl = NULL;
	readed = 0;
	if ((BUFFER_SIZE <= 0) || fd < 0)
		return (NULL);
	//buffer read process//
	while ((readed == read(fd, buff, BUFFER_SIZE)) > 0)
	{
		if (!buff)
			return (free(buff), NULL);
		if (readed <= -1)
			return (free(buff), NULL);
		ft_strjoin(aux, buff);
	}
}

int main ()
{
    int fd = open("texto.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return 1;
    }
	get_next_line(fd);
	return 0;
} 
