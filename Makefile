# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 14:44:05 by yparthen          #+#    #+#              #
#    Updated: 2024/05/11 15:21:56 by yparthen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGNAME = pipex

#	Folders
SRC_DIR = src
INC_DIR = include

#	Dir library
LIBFT_DIR = libft
# PRINTF_DIR = lib_c/ft_printf

#	library name
LIBFT = $(LIBFT_DIR)/libft.a
# PRINTF = $(PRINTF_DIR)/ft_printf.a

#	Compiler & flags
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
INC_FLAGS = -I$(INC_DIR)

#	source files
SRCS = 	main.c ft_parse.c split_add_slash.c \


# Objetivos predeterminados
all : $(LIBFT) $(PRINTF) $(PROGNAME)

# Rule for libft
$(LIBFT) :
	@ $(MAKE) -C $(LIBFT_DIR)

# # Rule for ft_printf
# $(PRINTF) : $(LIBFT)
# 	@ $(MAKE) -C $(PRINTF_DIR)

# Archivos objeto
OBJS := $(SRCS:%.c=$(SRC_DIR)/%.o)

# Rules
all: $(PROGNAME)

$(PROGNAME): $(OBJS) $(LIBFT) #$(PRINTF)
	@ $(CC) $(CFLAGS) $(INC_FLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) $(CFLAGS) $(INC_FLAGS) -c -o $@ $<

# Cleanning
clean :
	@ $(MAKE) -C $(LIBFT_DIR) clean
# @ $(MAKE) -C $(PRINTF_DIR) clean
	@ rm -f $(OBJS)

fclean : clean
	@ $(MAKE) -C $(LIBFT_DIR) fclean
# @ $(MAKE) -C $(PRINTF_DIR) fclean
	@ rm -f $(PROGNAME)

re: fclean all

.PHONY: all clean fclean re


# #SETUP
# NAME		=	pipex
# CC			=	gcc
# FLAGS		=	-Wall -Wextra -Werror
# RM			=	rm -rf

# #FILES AND PATH
# HEADER_SRCS	=	pipex.h
# HEADER_DIR	=	include/
# HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

# MPATH_SRCS	=	ft_parse.c split_add_slash.c
# MPATH_DIR	=	src/
# MPATH		=	$(addprefix $(MPATH_DIR), $(MPATH_SRCS))
# OBJ_M		=	$(MPATH:.c=.o)

# #BPATH_SRCS	=	pipex_bonus.c error_bonus.c here_doc_bonus.c\
# #				files_bonus.c free_bonus.c child_bonus.c
# #BPATH_DIR	=	bonus/
# #BPATH		=	$(addprefix $(BPATH_DIR), $(BPATH_SRCS))
# #OBJ_B		=	$(BPATH:.c=.o)

# #FUNC_SRCS	=	ft_strncmp.c ft_strdup.c ft_split.c ft_strjoin.c
# #FUNC_DIR	=	functions/
# #FUNC 		=	$(addprefix $(FUNC_DIR), $(FUNC_SRCS))\
# #				gnl/get_next_line_utils.c gnl/get_next_line.c
# #OBJ_F		=	$(FUNC:.c=.o)

# LIBFT_DIR = lib_c/libft

# LIBFT = $(LIBFT_DIR)/libft.a

# #COMMANDS
# %.o: %.c $(HEADER) Makefile
# 				@${CC} ${FLAGS} -c $< -o $@

# $(NAME):		$(OBJ_M) $(LIBFT)
# 				@$(CC) $(OBJ_M) -o $(NAME)
# 				@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

# all:			$(LIBFT) $(NAME)

# # Rule for libft
# $(LIBFT) :
# 	@ $(MAKE) -C $(LIBFT_DIR)
# #bonus:			$(OBJ_F) $(OBJ_B)
# #				@$(CC) $(OBJ_F) $(OBJ_B) -o $(NAME)
# #				@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

# clean:
# 				@$(RM) $(OBJ_M)
# #				@$(RM) $(OBJ_F)
# #				@$(RM) $(OBJ_B)
# 				@ $(MAKE) -C $(LIBFT_DIR) clean
# 				@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

# fclean:			clean
# 				@$(RM) $(NAME)
# 				@echo -e "$(RED)all deleted!$(DEFAULT)"

# re:				fclean all

# .PHONY:		all clean fclean bonus re

# #COLORS
# RED = \033[1;31m
# GREEN = \033[1;32m
# YELLOW = \033[1;33m
# DEFAULT = \033[0m





# SRC =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
# 		ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
# 		ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
# 		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
# 		ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
# 		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
# 		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
# 		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
# 		ft_putendl_fd.c ft_putnbr_fd.c

# SRC_BONUS =    ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
# 		 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
# 		ft_lstmap.c

# CC	=	clang
# CFLAGS	=	-Wall -Wextra -Werror -I.

# OBJ =    $(SRC:.c=.o)
# OBJ_BONUS =    $(SRC_BONUS:.c=.o)

# NAME = libft.a

# $(NAME) : $(OBJ)
# 		ar rcv $@ $^

# %.o : %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# all : $(NAME)

# bonus : $(NAME) $(OBJ_BONUS)
# 		ar rsv $(NAME) $(OBJ_BONUS)

# clean :
# 	rm -rf $(OBJ) $(OBJ_BONUS)

# fclean : clean
# 	rm -rf $(NAME)

# re : fclean all

# so:
# 	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
# 	gcc -nostartfiles -shared -o libft.so $(OBJ)

# .PHONY : re clean fclean so all
