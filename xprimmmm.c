#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 32

// Declaración de funciones
char *ft_strdup(const char *s1);
char *ft_strjoin(char *s1, char *s2);
char *ft_extract_line(char *aux);
char *ft_update_aux(char *aux);
char *get_next_line(int fd);

int main() {
    int fd = open("texto.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error al abrir el archivo");
        return 1;
    }
    char *line = get_next_line(fd);
    while (line) {
        printf("Linea leida --> %s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return 0;
}

char *get_next_line(int fd) {
    char *buff;
    char *gnl;
    static char *aux = NULL;
    ssize_t readed;

    // Verifica si el archivo es válido y el tamaño del buffer
    if (BUFFER_SIZE <= 0 || fd < 0)
        return NULL;

    // Asignación inicial de aux si no se ha asignado aún
    if (!aux)
        aux = ft_strdup("");

    // Asigna memoria para el búfer de lectura
    buff = malloc(BUFFER_SIZE + 1);
    if (!buff)
        return NULL;

    // Lee los datos del archivo
    readed = read(fd, buff, BUFFER_SIZE);
    if (readed < 0)
        return (free(buff), NULL);

    // Concatenación y búsqueda de salto de línea
    while (readed > 0) {
        buff[readed] = '\0';
        char *new_aux = ft_strjoin(aux, buff);  // Concatenar y liberar aux anterior
        free(aux);  // Liberamos la memoria de aux antes de reasignarla
        aux = new_aux;

        if (ft_strchr(buff, '\n'))
            break;

        readed = read(fd, buff, BUFFER_SIZE);
    }

    // Si no hay datos o se alcanzó el final del archivo
    if (!aux || aux[0] == '\0') {
        free(buff);
        free(aux);
        aux = NULL;
        return NULL;
    }

    // Extraemos la línea
    gnl = ft_extract_line(aux);
    aux = ft_update_aux(aux);

    // Liberar el búfer y retornar la línea
    free(buff);
    return gnl;
}

char *ft_extract_line(char *aux) {
    char *line;
    size_t y = 0;
    size_t i;

    if (!aux)
        return NULL;

    // Encontrar la posición del salto de línea o el final de la cadena
    while (aux[y] && aux[y] != '\n')
        y++;

    // Si encontramos un salto de línea, incrementamos para incluirlo
    if (aux[y] == '\n')
        y++;

    line = malloc(y + 1);
    if (!line)
        return NULL;

    // Copiar los datos hasta el salto de línea o el final
    i = 0;
    while (i < y) {
        line[i] = aux[i];
        i++;
    }
    line[i] = '\0';
    return line;
}

char *ft_update_aux(char *aux) {
    char *rest;
    size_t i = 0;
    size_t o = 0;

    if (!aux)
        return NULL;

    // Encontrar el salto de línea
    while (aux[i] && aux[i] != '\n')
        i++;

    if (aux[i] == '\n')
        i++;  // Saltamos el salto de línea

    if (i >= ft_strlen(aux)) {
        free(aux);
        return NULL;  // Si no hay más datos, liberamos aux
    }

    // Crear la nueva cadena con los datos restantes
    rest = malloc(ft_strlen(aux) - i + 1);
    if (!rest) {
        free(aux);
        return NULL;
    }

    // Copiar los datos restantes
    while (aux[i]) {
        rest[o] = aux[i];
        i++;
        o++;
    }
    rest[o] = '\0';

    // Liberar la memoria de la cadena original
    free(aux);
    return rest;
}

// Implementación de ft_strdup
char *ft_strdup(const char *s1) {
    size_t len = 0;
    while (s1[len])
        len++;
    char *dup = malloc(len + 1);
    if (dup) {
        for (size_t i = 0; i < len; i++) {
            dup[i] = s1[i];
        }
        dup[len] = '\0';
    }
    return dup;
}

// Implementación de ft_strjoin
char *ft_strjoin(char *s1, char *s2) {
    size_t len1 = 0, len2 = 0;
    while (s1[len1])
        len1++;
    while (s2[len2])
        len2++;

    char *joined = malloc(len1 + len2 + 1);
    if (!joined)
        return NULL;

    for (size_t i = 0; i < len1; i++)
        joined[i] = s1[i];
    for (size_t i = 0; i < len2; i++)
        joined[len1 + i] = s2[i];
    joined[len1 + len2] = '\0';

    return joined;
}
