# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrian <adrian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 18:42:18 by adrian            #+#    #+#              #
#    Updated: 2020/11/04 18:42:49 by adrian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_two

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