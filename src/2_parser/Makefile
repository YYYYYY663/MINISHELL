#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 18:05:31 by teando            #+#    #+#              #
#    Updated: 2024/12/23 19:11:02 by teando           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

DEBUGFLAGS  := -DFUNC_OUT
SRCS 		:= parser.c ast_root_new.c draft_parser_debug.c
CFLAGS		:= -Wall -Wextra



NAME		:= parser
CC			:= cc
LFLAGS		:= -lreadline
RM			:= rm -rf
ROOT_DIR	:= .
OUT_DIR		:= $(ROOT_DIR)/obj
INCS_DIR	:= ../../inc
LIBFT_DIR	:= ../../lib/libft
LIBSYS_DIR  := ../0_system
LIBLEX_DIR  := ../1_lexer

LIBLEX      := $(LIBLEX_DIR)/liblex.a
LIBSYS      := $(LIBSYS_DIR)/libsys.a
LIBFT		:= $(LIBFT_DIR)/libft.a
IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR)


	
OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

ifeq ($(DEBUG), 1)
	CFLAGS	+= -g -fsanitize=address
else
	CFLAGS	+= -O2
endif

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

# $(LIBFT): | $(LIBFT_DIR)/Makefile
# 	$(MAKE) -C $(LIBFT_DIR)

# $(LIBSYS): | $(LIBSYS_DIR)/Makefile
# 	$(MAKE) -C $(LIBSYS_DIR)

$(OUT_DIR)/%.o: $(ROOT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OUT_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)


test: $(NAME)
	@$(CC) -Wall -Wextra  $(IDFLAGS) $(DEBUGFLAGS) $(NAME) $(LIBFT) $(LIBSYS) $(LIBLEX) __2main.c -o test2XXXX
	@./test2XXXX
	@rm test2XXXX


.PHONY: all clean fclean re initsub sub norm debug

-include $(DEPS)