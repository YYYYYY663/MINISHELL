# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 18:05:31 by teando            #+#    #+#              #
#    Updated: 2025/01/04 22:02:26 by ymizukam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# DEBUGFLAGS  := #-DFUNC_OUT
# SRCS 		:= src/main.c
# CFLAGS		:= -Wall -Wextra



# NAME		:= minishell
# CC			:= cc
# LFLAGS		:= -lreadline
# RM			:= rm -rf
# ROOT_DIR	:= .
# OUT_DIR		:= $(ROOT_DIR)/obj
# INCS_DIR	:= inc
# LIBFT_DIR	:= lib/libft
# LIBSYS_DIR  := src/0_system
# LIBLEX_DIR  := src/1_lexer
# LIBPARS_DIR := src/2_parser
# LIBEXEC_DIR := src/3_executor
# LIBREDR_DIR := src/4_redirect
# LIBENV_DIR  := src/5_env

# LIBBLT_DIR  := src/7_builtin


# LIBFT		:= $(LIBFT_DIR)/libft.a
# LIBSYS      := $(LIBSYS_DIR)/libsys.a	
# LIBLEX      := $(LIBLEX_DIR)/liblex.a
# LIBPARS     := $(LIBPARS_DIR)/libpars.a
# LIBEXEC     := $(LIBEXEC_DIR)/libexec.a
# LIBREDR     := $(LIBREDR_DIR)/libredr.a
# LIBENV      := $(LIBENV_DIR)/libenv.a

# LIBBLT      := $(LIBBLT_DIR)/libblt.a

# IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR)


	
# OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
# DEPS		:= $(OBJS:.o=.d)

# ifeq ($(DEBUG), 1)
# 	CFLAGS	+= -g -fsanitize=address
# else
# 	CFLAGS	+= -O2
# endif

# all: $(NAME)

# $(NAME): $(LIBFT) $(LIBSYS) $(LIBLEX) $(LIBPARS) $(LIBENV) $(LIBREDR) $(LIBBLT) $(LIBEXEC) $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBSYS) $(LIBLEX) $(LIBPARS) $(LIBEXEC) $(LIBENV) $(LIBREDR) $(LIBBLT) $(LIBFT) -o $@


# $(LIBFT): | $(LIBFT_DIR)/Makefile
# 	$(MAKE) -C $(LIBFT_DIR)

# $(LIBSYS): $(LIBSYS_DIR)/Makefile
# 	$(MAKE) -C $(LIBSYS_DIR)

# $(LIBLEX): $(LIBLEX_DIR)/Makefile
# 	$(MAKE) -C $(LIBLEX_DIR)

# $(LIBPARS): $(LIBPARS_DIR)/Makefile
# 	$(MAKE) -C $(LIBPARS_DIR)

# $(LIBEXEC): $(LIBEXEC_DIR)/Makefile
# 	$(MAKE) -C $(LIBEXEC_DIR)

# $(LIBREDR): $(LIBREDR_DIR)/Makefile
# 	$(MAKE) -C $(LIBREDR_DIR)

# $(LIBENV): $(LIBENV_DIR)/Makefile
# 	$(MAKE) -C $(LIBENV_DIR)

# # $(LIBSIG): | $(LIBSIG_DIR)/Makefile
# # 	$(MAKE) -C $(LIBSIG_DIR)

# $(LIBBLT): $(LIBBLT_DIR)/Makefile
# 	$(MAKE) -C $(LIBBLT_DIR)


# $(OUT_DIR)/%.o: $(ROOT_DIR)/%.c
# 	@mkdir -p $(@D)
# 	$(CC) $(CFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

# clean:
# 	$(MAKE) -C $(LIBFT_DIR) clean
# 	$(MAKE) -C $(LIBSYS_DIR) clean
# 	$(MAKE) -C $(LIBLEX_DIR) clean
# 	$(MAKE) -C $(LIBPARS_DIR) clean
# 	$(MAKE) -C $(LIBEXEC_DIR) clean
# 	$(MAKE) -C $(LIBREDR_DIR) clean
# 	$(MAKE) -C $(LIBENV_DIR) clean

# 	$(MAKE) -C $(LIBBLT_DIR) clean
# 	$(RM) $(OUT_DIR)

# fclean: clean
# # $(MAKE) -C $(LIBFT_DIR) fclean
# 	$(MAKE) -C $(LIBSYS_DIR) fclean
# 	$(MAKE) -C $(LIBFT_DIR) fclean
# 	$(MAKE) -C $(LIBLEX_DIR) fclean
# 	$(MAKE) -C $(LIBPARS_DIR) fclean
# 	$(MAKE) -C $(LIBEXEC_DIR) fclean
# 	$(MAKE) -C $(LIBREDR_DIR) fclean
# 	$(MAKE) -C $(LIBENV_DIR) fclean

# 	$(MAKE) -C $(LIBBLT_DIR) fclean
# 	$(RM) $(NAME)

# re: fclean all

# $(LIBFT_DIR)/Makefile:
# 	git submodule update --init --recursive

# sub:
# 	git submodule update --remote

# norm:
# 	@norminette $(SRCS) $(INCS_DIR)

# debug:
# 	$(MAKE) DEBUG=1

# .PHONY: all clean fclean re initsub sub norm debug

# -include $(DEPS)

# test: $(NAME)
# 	@$(CC) -Wall -Wextra  $(IDFLAGS) $(DEBUGFLAGS) $(NAME) $(LIBFT) $(LIBSYS) $(LIBLEX) $(LIBPARS) $(LIBENV) $(LIBREDR) $(LIBBLT) __3main.c -o test3XXXX
# 	@./test3XXXX
# 	@rm -rf test3XXXX




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
    $(addprefix src/, \
        $(addprefix 0_system/, \
            system_exit.c system_init.c xalloc.c xunistd.c ast_utils.c token_utils.c \
        ) \
        $(addprefix 1_lexer/, \
            allocate_token.c lexer_handler.c lexer_main_loop.c tokenizer.c validate_syntax.c \
        ) \
        $(addprefix 2_parser/, \
            parser.c ast_new.c draft_parser_debug.c _ast_utils.c \
        ) \
        $(addprefix 3_executor/, \
            executor.c ast_traverse.c _ast_node.c _exec_utils.c \
        ) \
        $(addprefix 4_redirect/, \
            redirect_dispacher.c heredoc.c \
        ) \
        $(addprefix 5_env/, \
            _env_utils.c env_export.c env_get.c env_unset.c \
            path_diapacher.c _path_absolute.c _path_relative.c _path_home.c \
            var_dispacher.c \
        ) \
        $(addprefix 6_signals/, \
        ) \
        $(addprefix 7_builtin/, \
            _builtin_env.c _builtin_unset.c _builtin_exit.c builtin_dispatcher.c _builtin_cd.c \
            _builtin_export.c _builtin_echo.c _builtin_pwd.c \
        ) \
        main.c \
    )

	
OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

ifeq ($(DEBUG), 1)
	CFLAGS	+= -g -fsanitize=address
else
	CFLAGS	+= -O2
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