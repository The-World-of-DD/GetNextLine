/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dierojas < dierojas@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:33:01 by dierojas          #+#    #+#             */
/*   Updated: 2025/02/17 19:18:24 by dierojas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//tengo que ver como utilizo este coso sin que me pegue un tiro
//static char	*the_line;

char    *get_next_line(int fd)
{
    char	*the_line;
    return (the_line);
}

//RESERVA DE MEMORIA DE LO QUE TENGAMOS QUE HACER

//habra que contar los caracteres para reservar con malloc lo que se va a imprimir
//tenemos que ver que en funcion de como se imprima se reserva?? 
//---> COmo interacciona con el biffer¿?¿?¿?

//DE ALGUNA MANERA, TENDREMOS QUE IR LEYENDO Y PASANDOSELO 

//que lo imprima de alguna manera
//debe de leer la linea hasta que encuentre un \n

//que sea capaz de saltar a la siguiente linea con las condiciones de:
// -> Si no hay error || no hay nada que leer = NULL
//el buffer es variable, hay que tener cierta antelacion
//--> Tengo que ver como juego con el BufferSize

//Tiene un comportamiento indeterminado cuando se cambia el fd
//Comportamiento indeterminado cuando es un archivo binario
//¿Que es un archivo binario? xddddd
