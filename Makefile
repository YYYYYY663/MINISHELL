# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 18:05:31 by teando            #+#    #+#              #
#    Updated: 2025/01/27 12:03:44 by ymizukam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra #-Werror
LFLAGS		:= -lreadline
RM			:= rm -rf
ROOT_DIR	:= .
OUT_DIR		:= $(ROOT_DIR)/obj
INCS_DIR	:= $(ROOT_DIR)/inc
LIBFT_DIR	:= $(ROOT_DIR)/lib/libft
LIBFT		:= $(LIBFT_DIR)/libft.a
IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR)

SRCS 		:= \
    $(shell find src -type f -name "*.c")

    # $(addprefix src/, \
    #     $(addprefix 0_system/, \
    #         system_exit.c system_init.c xalloc.c xunistd.c ast_utils.c token_utils.c  readline.c\
    #     ) \
    #     $(addprefix 1_lexer/, \
    #         allocate_token.c lexer_handler.c lexer_main_loop.c tokenizer.c validate_syntax.c \
    #     ) \
    #     $(addprefix 2_parser/, \
    #         parser.c ast_new.c draft_parser_debug.c \
    #     ) \
    #     $(addprefix 3_executor/, \
    #         executor.c ast_traverse.c _ast_node.c _ast_pipeline.c _exec_utils.c \
    #     ) \
    #     $(addprefix 4_redirect/, \
    #         redirect_dispatcher.c _heredoc.c _redirect.c\
    #     ) \
    #     $(addprefix 5_env/, \
    #         _env_utils.c map_export.c env_get.c map_unset.c \
    #         path_diapacher.c _path_absolute.c _path_relative.c _path_home.c \
    #         var_dispatcher.c \
    #     ) \
    #     $(addprefix 6_signals/, \
	# 		signal_handler.c \
    #     ) \
    #     $(addprefix 7_builtin/, \
    #         _builtin_env.c _builtin_unset.c _builtin_exit.c builtin_dispatcher.c _builtin_cd.c \
    #         _builtin_export.c _builtin_echo.c _builtin_pwd.c \
    #     ) \
    #     $(addprefix 8_alias/, \
    #         alias_update.c alias_file_parser.c \
    #     ) \
    #     main.c \
    # )

	
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

neko:
	echo wanwan

.PHONY: all clean fclean re initsub sub norm debug neko

-include $(DEPS)