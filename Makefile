# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 16:18:41 by hakahmed          #+#    #+#              #
#    Updated: 2023/04/10 19:25:35 by hakahmed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ==== ==== MY PIPEX MAKEFILE :D ==== ==== #

NAME = pipex

# ==== ==== THE BEST PIPEX : ' D ==== ==== #




# ==== ==== COMPILER ==== ==== #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

# CFLAGS += -fsanitize=address -g3

# ==== ==== END ==== ==== #




# ==== ==== LIB ==== ==== #

LIBNAME = libft.a

LIBDIR = libft

LIB = $(LIBDIR)/$(LIBNAME)

LFTINC = -I $(LIBDIR)/$(INC)

LDFLAGS = -L $(LIBDIR) -lft

# ==== ==== END ==== ===== # 




# ==== ==== SRC ==== ==== #

SRCDIR = srcs

SRCFILES = main.c \
	   envparser.c \
	   error_handling.c \
	   utils.c \
	   heredoc.c

SRCS = $(addprefix $(SRCDIR)/,$(SRCFILES))

# ==== ==== END ==== ==== #




# ==== ==== INC ==== ==== #

INC = inc
IFLAGS = -I $(INC)

# ==== ==== END ==== ==== #




# ==== ==== OBJS ==== ==== #

OBJDIR = .obj

OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

$(OBJDIR)/%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) $(LFTINC) -c $< -o $@
	@echo "$(bold)[ $(COLOUR_GREEN)OK $(COLOUR_END)$(bold)] $(reset)" $<

# ==== ==== END ==== ==== #


# ==== ==== COLORS ==== ==== #

bold := $(shell tput bold)
reset := $(shell tput sgr0)

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

# ==== ===== END ==== ===== #


# ==== ==== RULES ==== ==== #

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(LFTINC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(COLOUR_RED)$(bold)run the program by executing ./$(NAME) infile cmd1 cmd2 outfile $(reset)"

all: $(NAME)

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

prt:
	@curl parrot.live
