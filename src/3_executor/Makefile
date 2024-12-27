
DEBUGFLAGS  := #-DFUNC_OUT
SRCS 		:= executor.c exec_traverse.c
CFLAGS		:= -Wall -Wextra



NAME		:= libexec.a
CC			:= cc
LFLAGS		:= -lreadline
RM			:= rm -rf
ROOT_DIR	:= .
OUT_DIR		:= $(ROOT_DIR)/obj
INCS_DIR	:= ../../inc
LIBFT_DIR	:= ../../lib/libft
LIBSYS_DIR  := ../0_system
LIBLEX_DIR  := ../1_lexer
LIBPARS_DIR := ../2_parser
LIBENV_DIR  := ../5_env
LIBREDR_DIR := ../4_redirect
LIBBLT_DIR  := ../7_builtin


LIBBLT      := $(LIBBLT_DIR)/libblt.a
LIBREDR     := $(LIBREDR_DIR)/libredr.a
LIBENV      := $(LIBENV_DIR)/libenv.a
LIBPARS     := $(LIBPARS_DIR)/libpars.a
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
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

clean:
	$(RM) $(OUT_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

test: $(NAME)
	@$(CC) -Wall -Wextra  $(IDFLAGS) $(DEBUGFLAGS) $(NAME) $(LIBFT) $(LIBSYS) $(LIBLEX) $(LIBPARS) $(LIBENV) $(LIBREDR) $(LIBBLT) __3main.c -o test3XXXX
	@./test3XXXX
	@rm -rf test3XXXX


.PHONY: all clean fclean re initsub sub norm debug

-include $(DEPS)