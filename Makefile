# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 16:18:41 by hakahmed          #+#    #+#              #
#    Updated: 2023/04/19 12:05:29 by hakahmed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ==== ==== MY PIPEX MAKEFILE :D ==== ==== #

NAME = pipex

# ==== ==== THE BEST PIPEX : ' D ==== ==== #




# ==== ==== COMPILER ==== ==== #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

# ==== ==== END ==== ==== #




# ==== ==== LIB ==== ==== #

LIBNAME = libft.a

LIBDIR = libft

LIB = $(LIBDIR)/$(LIBNAME)

CFLAGS += -I $(LIBDIR)/$(INC)

LDFLAGS = -L $(LIBDIR) -lft

# ==== ==== END ==== ===== # 




# ==== ==== SRC ==== ==== #

SRCDIR = srcs

SRCFILES = main.c \
	   envparser.c \
	   error_handling.c \
	   utils.c \
	   heredoc.c \
	   init.c \
	   redirect.c

SRCS = $(addprefix $(SRCDIR)/,$(SRCFILES))

# ==== ==== END ==== ==== #




# ==== ==== INC ==== ==== #

INC = inc
CFLAGS += -I $(INC)

# ==== ==== END ==== ==== #


BFLAGS = -D BONUS=

BTRUE = $(BFLAGS)1 
BFALSE = $(BFLAGS)0 


# ==== ==== OBJS ==== ==== #

OBJDIR = .obj

OBJS = $(addprefix $(OBJDIR)/,$(SRCFILES:.c=.o))

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

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $^ $(LDFLAGS) -o $@
	@echo "$(COLOUR_RED)$(bold)run the program by executing ./$(NAME) infile cmd1 cmd2 outfile $(reset)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) 
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(bold)[ $(COLOUR_GREEN)OK $(COLOUR_END)$(bold)] $(reset)" $<

$(OBJDIR):
	@mkdir -p $@

clean:
	make fclean -C libft
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

sanitize: CFLAGS += -g3 -fsanitize=address
sanitize: LDFLAGS += -fsanitize=address
sanitize: rebonus 


bonus: CFLAGS += $(BTRUE)
bonus: all

rebonus: fclean bonus

prt:
	@curl parrot.live

.SILENT: clean fclean

.PHONY: all clean fclean re bonus prt
