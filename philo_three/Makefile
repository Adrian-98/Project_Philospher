# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 18:42:18 by adrian            #+#    #+#              #
#    Updated: 2020/11/05 20:17:37 by amunoz-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_three

SRCS		= main.c extras.c ft_body.c ft_life.c ft_write.c semaphores.c

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