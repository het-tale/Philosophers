# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 20:53:06 by het-tale          #+#    #+#              #
#    Updated: 2022/09/17 22:48:07 by het-tale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =    philo_bonuss

SRCS    =   ./philo_bonus/*.c

OBJCT    =    ${SRCS:.c=.o}

FLAGS    =    -Wall -Wextra -Werror -pthread #-fsanitize=address

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
