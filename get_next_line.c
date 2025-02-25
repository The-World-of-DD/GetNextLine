/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas <dierojas@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/02/25 09:46:50 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static char	*buff;
	static char	*aux;
	char	*gnl;
	char	rest;
	ssize_t	readed;
	aux = ft_strdup("");
	
	//aqyi hacemos que se lea el tema, que no sera hasta que termine linea o EOF
	while (readed != EOF || readed > 0)//(1)//aqui puedo dejar un 0 teniendo encuenta el stdin??
	{
		if (readed == -1)
			return (free(buff), NULL);
		if (!buff)
			return (free(buff), NULL);
		readed = read(fd, buff, BUFFER_SIZE);
		aux = ft_strjoin(aux, readed);
		break;
	}
	rest = ft_strdup("");
	if (ft_strchr(aux, '\n'))
		rest = ft_strdup(aux);//aqui no se como hacer que duplique desde \n hasta delante--> 
	//ahora tenemos que ver donde se ha quedado la \n, duplicar lo que hay en adelante
	//Necesitamos leer el buffer y copiarlo en aux--> El buffer hay que liberarlo cada vez que se utiliza
	//Aqui ponemos el reciclador de basura o averiguamos en rest
	
	ft_trash_management(rest, aux);

	
	gnl = malloc(ft_strlen(aux) - ft_strlen(rest) + 1);// que pasa si rest no existe????
	if (!gnl)
		return (free(buff), NULL);
	while (gnl != '\n')
		ft_strcpy(gnl, aux);
	gnl = '\0';
	return (gnl);
}


char	*ft_trash_management(char *aux);
{
	size_t	i;
	size_t	k;
	char	*rest;
	
	i = ft_strlen(rest);
	k = 0;
	rest = ft_strdup("");
	while (rest[i] != '\n')
	{
		rest[i] = aux[k];
		i--;
		k++
	}
	rest[i] = '\0';
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
	get_next_line(0);
	return 0;
} 