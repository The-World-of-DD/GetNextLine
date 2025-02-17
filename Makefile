# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dierojas < dierojas@student.42madrid.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 21:21:44 by dierojas          #+#    #+#              #
#    Updated: 2025/02/17 11:24:35 by dierojas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME: get_next_line
SOURCES: 
OBJS: $(SOURCES:.c=.o)
BUFF: buffer#aqui tenemos que ver como meto el buffer
CC: gcc
FLAGS: -Wall -Werror -Wextra -$(BUFF)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) -r $@ $?

%.o: %.c
	$(CC) -c $(FLAGS) $(BUFF)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
