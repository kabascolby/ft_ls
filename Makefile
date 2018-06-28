# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/02 02:27:45 by tadey             #+#    #+#              #
#    Updated: 2018/06/24 11:08:00 by lkaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAGS = -Wall -Wextra -Werror
FILES = $(wildcard *.c)
OFILES = $(patsubst %.c, %.o, $(FILES))
LIBFT = libft.a

all: $(NAME)


$(NAME): $(LIBFT) $(OFILES)
	@gcc $(FLAGS) $(OFILES) libft/$(LIBFT) -o $@

$(LIBFT):
	@make -C libft
	@make libft/ft_printf

%.o: %.c
	gcc $(FLAGS) -c $<

clean:
	@/bin/rm -f $(FILES:.c=.o)
	@make clean -C libft
	echo "@make clean libft/ft_printf"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft
	echo "@make fclean libft/ft_printf"

re: fclean all
