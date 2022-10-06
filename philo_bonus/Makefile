# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 20:53:06 by het-tale          #+#    #+#              #
#    Updated: 2022/10/06 18:44:04 by het-tale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =    philo_bonus

SRCS    =   atoi_bonus.c init_close.c main.c philo_bonus.c philo_bonus_utils.c routines_bonus.c

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
