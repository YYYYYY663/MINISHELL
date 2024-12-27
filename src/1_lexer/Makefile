
DEBUGFLAGS  := #-DFUNC_OUT


#変更を加えるかもしれないものと分ける



NAME        := liblex.a
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCS_DIR	:= ../../inc
LIBFT_DIR	:= ../../lib/libft
LIBFT		:= $(LIBFT_DIR)/libft.a
LIBSYS_DIR  := ../0_system
LIBSYS     := $(LIBSYS_DIR)/libsys.a
IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR)

RM          := rm -rf
ROOT_DIR    := .
OUT_DIR     := $(ROOT_DIR)/obj
SRCS        := allocate_token.c lexer_handler.c lexer_main_loop.c tokenizer.c validate_syntax.c
OBJS        := $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS        := $(OBJS:.o=.d)

# コンパイルの最適化設定
ifeq ($(DEBUG), 1)
    CFLAGS   += -g -fsanitize=address
else
    CFLAGS   += -O2
endif


all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

$(LIBFT): | $(LIBFT_DIR)/Makefile
	$(MAKE) -C $(LIBFT_DIR)

$(LIBSYS): | $(LIBSYS_DIR)/Makefile
	$(MAKE) -C $(LIBSYS_DIR)

$(OUT_DIR)/%.o: $(ROOT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OUT_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all


test: $(NAME)
	@$(CC) -Wall -Wextra  $(IDFLAGS) $(DEBUGFLAGS) $(NAME) $(LIBFT) $(LIBSYS) __1main.c -o test1XXXX
	@./test1XXXX
	@rm test1XXXX






-include $(DEPS)

.PHONY: all clean fclean re
