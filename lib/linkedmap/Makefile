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


NAME		:= libmap.a
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR			:= ar rcs
RM			:= rm -rf
ROOT_DIR	:= ..
OUT_DIR		:= obj
INCS_DIR	:= .
LIBFT_DIR	:= ../libft
LIBFT		:= $(LIBFT_DIR)/libft.a
IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR)

SRCS 		:= lmap_get.c callback.c lmap_export.c lmap_unset.c

	
OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

$(LIBFT): | $(LIBFT_DIR)/Makefile
	$(MAKE) -C $(LIBFT_DIR)

$(OUT_DIR)/%.o: %.c
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