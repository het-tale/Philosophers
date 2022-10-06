# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 20:53:06 by het-tale          #+#    #+#              #
#    Updated: 2022/10/06 20:43:45 by het-tale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =    philo

SRCS    =    philo.c atoi.c routines.c conditions.c philo_utils.c main.c

OBJCT    =    ${SRCS:.c=.o}

FLAGS    =    -Wall -Wextra -Werror -pthread

RM        =    rm -f

CC        =    cc

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) -g

clean :
	${RM} ${OBJCT}

fclean : clean
	${RM} ${NAME}

re : fclean all
