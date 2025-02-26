/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas < dierojas@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/02/26 02:20:59 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_trash_management(char *aux);

char    *get_next_line(int fd)
{
	static char	*buff;
	char	*aux;
	char	*gnl;
	char	*rest;
	ssize_t	readed;
	//char	*tmp;//lo usamos para dejar el resto
	size_t	i;

	aux = ft_strdup("");
	rest = ft_strdup("");
	readed = 0;//aqyi hacemos que se lea el tema, que no sera hasta que termine linea o EOF
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	buff[readed] = '\0';
	while (readed = read(fd, buff, BUFFER_SIZE) > 0)
	{
		if (readed <= -1)
			return (free(buff), NULL);
		if (!buff)
			return (free(buff), NULL);
		readed = read(fd, buff, BUFFER_SIZE);
		aux = ft_strjoin(aux, buff);
		break;
	}
	rest = NULL;
	if (ft_strchr(aux, '\n'))
	{
		free (rest);
		rest = ft_strdup(aux);//aqui no se como hacer que duplique desde \n hasta delante-->
	}
	ft_trash_management(aux);
	gnl = malloc(ft_strlen(aux) - ft_strlen(rest) + 1);// que pasa si rest no existe????
	if (!gnl)
		return (free(buff), NULL);
	i = 0;
	while (gnl[i] != '\n')
		ft_strcpy(gnl, aux);
	gnl[i] = '\0';
	free(aux);
	return (gnl);
}

char	*ft_trash_management(char *aux)
{
	size_t	i;
	size_t	k;
	char	*rest;
	
	free(rest);
	rest = NULL;
	if (!rest)
		return (NULL);
	i = 0;
	k = 0;
	while (aux[i])
	{
		while (aux[i] != '\n')
			i++;
		if (aux[i] == '\n')
			ft_strdup(ft_strchr(aux, '\n') + 1),
	}
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
	get_next_line(fd);
	return 0;
} 
