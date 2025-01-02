
DEBUGFLAGS  := -DFUNC_OUT
SRCS        := _env_utils.c env_export.c env_get.c env_unset.c \
			   path_diapacher.c _path_absolute.c _path_relative.c _path_home.c \
			   var_dispacher.c


CFLAGS      := -Wall -Wextra 



NAME        := libenv.a
CC          := cc
INCS_DIR	:= ../../inc
LIBFT_DIR	:= ../../lib/libft
LIBFT		:= $(LIBFT_DIR)/libft.a
LIBSYS_DIR  := ../0_system
LIBSYS     := $(LIBSYS_DIR)/libsys.a
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

$(LIBFT): | $(LIBFT_DIR)/Makefile
	$(MAKE) -C $(LIBFT_DIR)

$(LIBSYS): | $(LIBSYS_DIR)/Makefile
	$(MAKE) -C $(LIBSYS_DIR)

$(OUT_DIR)/%.o: $(ROOT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

clean:
	$(RM) $(OUT_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all


env: $(NAME)
	@$(CC) -Wall -Wextra  $(IDFLAGS) $(DEBUGFLAGS) $(NAME) $(LIBFT) $(LIBSYS) __main_env.c -o test1XXXX
	@./test1XXXX
	@rm test1XXXX

path: $(NAME)
	@$(CC) -Wall -Wextra  $(IDFLAGS) $(DEBUGFLAGS) $(NAME) $(LIBFT) $(LIBSYS) __main_path.c -o test4XXXX
	@./test4XXXX
	@rm test4XXXX

var: $(NAME)
	@$(CC) -Wall -Wextra  $(IDFLAGS) $(DEBUGFLAGS) $(NAME) $(LIBFT) $(LIBSYS) __main_var.c -o test5XXXX
	@./test5XXXX
	@rm test5XXXX




-include $(DEPS)

.PHONY: all clean fclean re
