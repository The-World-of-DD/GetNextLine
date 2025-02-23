/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas <dierojas@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/02/23 22:52:29 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static char	*buff;
	static char	*aux;
	char	*gnl;
	ssize_t	readed;

	           aux = ft_strdup("");
	//aqyi hacemos que se lea el tema, que no sera hasta que encuentre \n o encuentre eof (== 0)
	while (1)
	{
		if (readed == -1)
			return (free(buff), NULL);
		if (!buff)
			return (free(buff), NULL);
		readed = read(fd, buff, BUFFER_SIZE);
		break;
	}
	
//Necesitamos leer el buffer y copiarlo en aux--> El buffer hay que liberarlo cada vez que se utiliza

	gnl = malloc(ft_strlen(aux) + 1);
	if (!gnl)
		return (NULL);
	return (gnl);
}

#include <fcntl.h>
int main ()
{
    int fd = open("texto.txt", O_RDONLY);
    if (fd == -1)
    {
        write(1, "Error al abrir el archivo", 25);
        return 1;
    }
} 