
DEBUGFLAGS  := -DFUNC_OUT
SRCS        := heredoc.c


CFLAGS      := -Wall -Wextra 



NAME        := libredr.a
CC          := cc
INCS_DIR	:= ../../inc

LIBFT_DIR	:= ../../lib/libft
LIBFT		:= $(LIBFT_DIR)/libft.a

LIBSYS_DIR  := ../0_system
LIBSYS     := $(LIBSYS_DIR)/libsys.a

LIBENV_DIR  := ../5_env
LIBENV      := $(LIBENV_DIR)/libenv.c



IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR)

RM          := rm -rf
ROOT_DIR    := .
OUT_DIR     := $(ROOT_DIR)/obj
OBJS        := $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS        := $(OBJS:.o=.d)

ifeq ($(DEBUG), 1)
    CFLAGS   += -g -fsanitize=address
else
    CFLAGS   += -O2
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
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OUT_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all


test: $(NAME)
	@$(CC) -Wall -Wextra  $(IDFLAGS) $(DEBUGFLAGS) $(NAME) $(LIBFT) $(LIBSYS) $(LIBENV) __4main.c -o test1XXXX
	@./test1XXXX
	@rm test1XXXX




-include $(DEPS)

.PHONY: all clean fclean re
