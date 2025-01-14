#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 18:05:31 by teando            #+#    #+#              #
#    Updated: 2025/01/12 20:15:10 by teando           ###   ########.fr        #
#                                                                              #
#******************************************************************************#


NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
LFLAGS		:= -lreadline
RM			:= rm -rf
ROOT_DIR	:= .
OUT_DIR		:= $(ROOT_DIR)/obj
INCS_DIR	:= $(ROOT_DIR)/inc $(ROOT_DIR)/sys
LIBFT_DIR	:= $(ROOT_DIR)/lib/libft
LIBMAP_DIR		:= $(ROOT_DIR)/lib/linkedmap

LIBFT		:= $(LIBFT_DIR)/libft.a
LIBMAP      := $(MAP_DIR)/libmap.a
IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR) -I$(MAP_DIR)

SRCS 		:= \
	SRC = $(shell find src -name "*.c") $(shell find util -name "*.c") 

    # $(addprefix src/, \
    #     main.c \
		
    # )\
	# $(addprefix util/, \
        
        
    # )

	
OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

ifeq ($(DEBUG), 1)
	CFLAGS	+= -g -fsanitize=address
else
	CFLAGS	+= 
endif

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMAP) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) $(LIBMAP) -o $@

$(LIBFT): | $(LIBFT_DIR)/Makefile
	$(MAKE) -C $(LIBFT_DIR)

$(LIBMAP): | $(LIBMAP_DIR)/Makefile
	$(MAKE) -C $(LIBMAP_DIR)

$(OUT_DIR)/%.o: $(ROOT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBMAP_DIR) clean
	$(RM) $(OUT_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBMAP_DIR) fclean
	$(RM) $(NAME)

re: fclean all

$(LIBFT_DIR)/Makefile:
	git submodule update --init --recursive

sub:
	git submodule update --remote

norm:
	@norminette $(SRCS) $(INCS_DIR)

debug:
	$(MAKE) DEBUG=1

.PHONY: all clean fclean re initsub sub norm debug

-include $(DEPS)