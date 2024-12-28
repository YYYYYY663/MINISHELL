
DEBUGFLAGS  := #-DFUNC_OUT
SRCS        :=  _builtin_env.c _builtin_unset.c _builtin_exit.c builtin_dispatcher.c _builtin_cd.c  \
                _builtin_export.c _builtin_echo.c _builtin_pwd.c


CFLAGS      := -Wall -Wextra 



NAME        := libblt.a
CC          := cc
INCS_DIR	:= ../../inc

LIBFT_DIR	:= ../../lib/libft
LIBFT		:= $(LIBFT_DIR)/libft.a

LIBSYS_DIR  := ../0_system
LIBSYS     := $(LIBSYS_DIR)/libsys.a

LIBENV_DIR  := ../5_env
LIBENV      := $(LIBENV_DIR)/libenv.a



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
	$(RM) $(OUT_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all


test: $(NAME)
	@$(CC) -Wall -Wextra  $(IDFLAGS) $(DEBUGFLAGS) $(NAME) $(LIBFT) $(LIBSYS) $(LIBENV) __7main.c -o test1XXXX
	@./test1XXXX
	@rm test1XXXX




-include $(DEPS)

.PHONY: all clean fclean re
