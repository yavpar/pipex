# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 14:44:05 by yparthen          #+#    #+#              #
#    Updated: 2024/06/04 14:09:17 by yparthen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGNAME = pipex

#	Folders
SRC_DIR = src
INC_DIR = include

#	Dir library
LIBFT_DIR = libft

#	library name
LIBFT = $(LIBFT_DIR)/libft.a

#	Compiler & flags
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
INC_FLAGS = -I$(INC_DIR)

#	source files
SRCS = 	main.c ft_parse.c split_add_slash.c ft_files.c \
		pipex.c ft_wait_pids.c destroy_list.c

# Objetivos predeterminados
all : $(LIBFT) $(PROGNAME)

# Rule for libft
$(LIBFT) :
	@ $(MAKE) -C $(LIBFT_DIR)

# object files
OBJS := $(SRCS:%.c=$(SRC_DIR)/%.o)

# Rules
all: $(PROGNAME)

$(PROGNAME): $(OBJS) $(LIBFT)
	@ $(CC) $(CFLAGS) $(INC_FLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) $(CFLAGS) $(INC_FLAGS) -c -o $@ $<

# Cleanning
clean :
	@ $(MAKE) -C $(LIBFT_DIR) clean
	@ rm -f $(OBJS)

fclean : clean
	@ $(MAKE) -C $(LIBFT_DIR) fclean
	@ rm -f $(PROGNAME)

re: fclean all

.PHONY: all clean fclean re
