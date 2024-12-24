NAME        := liblexer.a
CC          := cc
CFLAGS      := -Wall -Wextra #-Werror todo
INCS_DIR	:= ../../inc
LIBFT_DIR	:= ../../lib/libft
LIBFT		:= $(LIBFT_DIR)/libft.a
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

# 全体のターゲット
all: $(NAME)

# 静的ライブラリの作成
$(NAME): $(LIBFT) $(OBJS)
	ar rcs $@ $(OBJS)


$(LIBFT): | $(LIBFT_DIR)/Makefile
	$(MAKE) -C $(LIBFT_DIR)

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

# クリーンターゲット
clean:
	$(RM) $(OUT_DIR)

fclean: clean
	$(RM) $(NAME)

# 再ビルド
re: fclean all

# 依存ファイルをインクルード
-include $(DEPS)

.PHONY: all clean fclean re
