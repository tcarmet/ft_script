#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/19 17:20:13 by tcarmet           #+#    #+#              #
#    Updated: 2015/05/19 18:34:12 by tcarmet          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= ft_script

DEBUG		= no
ifeq ($(DEBUG),no)
    FLAG	= -Wall -Werror -Wextra
else
    FLAG	=-g3
endif

SRC		= ft_script.c

OBJ		= $(SRC:.c=.o)

INCDIR		= ./includes/

INCDIRLIB	= ./libft/includes/

SRCDIR		= ./srcs/

OBJDIR		= ./objs/

SRCS		= $(addprefix $(SRCDIR), $(SRC))

OBJS		= $(addprefix $(OBJDIR), $(OBJ))

.SILENT:

all:	$(NAME)

$(NAME):
ifeq ($(DEBUG),yes)
		echo "\\033[1;31mDEBUG COMPILATION.. (no flags except -g)\\033[0;39m"
else
		echo "\\033[1;31mCompilation with -Wall -Wextra -Werror...\\033[0;39m"
endif
		echo "\\033[1;34mGenerating objects... Please wait.\\033[0;39m"
			printf "\\033[44m"
			printf "        "
			git submodule init
			printf "        "
			git submodule update
			printf "        "			
			make -C libft/
			printf "        "
			gcc $(FLAG) -c $(SRCS) -I $(INCDIR) -I $(INCDIRLIB)
			printf "        "
			mkdir -p $(OBJDIR) ; mv $(OBJ) $(OBJDIR)
			printf "        "
			gcc $(FLAG) -o $(NAME) $(OBJS) -L ./libft/ -lft
			printf "        "
			printf "\\033[0;39m\n"

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all

git:
	git add .
	echo "Enter Your Commit : "
	read root_path ; git commit -m "$$root_path"
	git push
