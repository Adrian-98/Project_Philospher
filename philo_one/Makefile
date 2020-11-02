# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/21 19:37:10 by amunoz-p          #+#    #+#              #
#    Updated: 2020/11/02 19:51:36 by amunoz-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_one

SRCS		= main.c extras.c ft_body.c ft_life.c ft_write.c

OBJS		=	$(SRCS:.c=.o)

GCC			=	@gcc -Wall -Wextra -Werror

LIBS			= -lpthread

INCLUDES	=	./

all: $(NAME)

$(NAME):	$(OBJS)
		@$(GCC) -I$(INCLUDES) $(OBJS) -o $(NAME) $(LIBS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re