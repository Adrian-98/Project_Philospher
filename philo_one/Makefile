# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amunoz-p <amunoz-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/21 19:37:10 by amunoz-p          #+#    #+#              #
#    Updated: 2020/10/21 20:34:12 by amunoz-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philosopher

SRCS		= main.c extras.c

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