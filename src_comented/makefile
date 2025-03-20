# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: urlooved <urlooved@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 14:24:24 by urlooved          #+#    #+#              #
#    Updated: 2025/03/14 14:31:07 by urlooved         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf
SRCS = main.c \
		0_1_process.c \
		handler_parser.c \
		handler_t_philo.c \
		handler_t_stop_program.c \
		tools_init.c \
		tools_observers.c \
		tools_setters.c \
		tools_philo_actions.c \
		tools_free.c \
		tools_time.c \
		tools_print.c \
		tools_strs.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(EXTRA) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all