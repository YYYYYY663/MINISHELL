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
LIBFT		:= $(LIBFT_DIR)/libft.a
IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR)

SRCS 		:= \
    $(addprefix src/, \
        
        main.c \
    )

	
OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

ifeq ($(DEBUG), 1)
	CFLAGS	+= -g -fsanitize=address
else
	CFLAGS	+= 
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $@

$(LIBFT): | $(LIBFT_DIR)/Makefile
	$(MAKE) -C $(LIBFT_DIR)

$(OUT_DIR)/%.o: $(ROOT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OUT_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
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