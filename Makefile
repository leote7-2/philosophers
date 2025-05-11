# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 00:25:15 by joaoleote         #+#    #+#              #
#    Updated: 2025/05/08 00:24:39 by joaoleote        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	src/data_init.c \
		src/dinner.c \
		src/main.c \
		src/monitor_threads.c \
		src/init.c \
		src/utils.c \
		src/utils2.c \

OBJS = $(SRCS:.c=.o)
RM = rm -f $(OBJS)
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re