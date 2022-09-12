# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 20:53:06 by het-tale          #+#    #+#              #
#    Updated: 2022/09/12 15:33:11 by het-tale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =    philo

SRCS    =    philo.c atoi.c routines.c

OBJCT    =    ${SRCS:.c=.o}

FLAGS    =    -Wall -Wextra -Werror -pthread -fsanitize=thread

RM        =    rm -f

CC        =    gcc

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) -g

clean :
	${RM} ${OBJCT}

fclean : clean
	${RM} ${NAME}

re : fclean all
