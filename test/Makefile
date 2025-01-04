CFLAGS		:= -Wall -Wextra
VALGRIND    := valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q

OBJDIR       := ../obj/src

CC			:= cc
CFLAGS		:= -Wall -Wextra
LIBFT_DIR	:= ../lib/libft
INCS_DIR    := ../inc

IFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR)
LFLAGS		:= -lreadline
DFLAGS      := -DFUNC_OUT



SYSTEM      := ../src/0_system/*.c
LEXER       := ../src/1_lexer/*.c
PARSER      := ../src/2_parser/*.c
EXECUTOR    := ../src/3_executor/*.c
REDIRECT    := ../src/4_redirect/*.c
ENV         := ../src/5_env/*.c
SIGNAL     	:= ../src/6_signal/*.c
BUILTIN     := ../src/7_builtin/*.c


COMPILE     :=  $(CC) $(IFLAGS) $(CFLAGS) $(DFLAGS) $(LFLAGS)

.PHONY: all libft system lexer parser semantic

all: libft

libft:
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a libft.a


system:
	$(COMPILE) $(SYSTEM) 0_test/system_main.c libft.a -o system.out
	$(VALGRIND) ./system.out
	rm -f system.out


lexer:
	$(COMPILE) $(SYSTEM) $(LEXER) 1_test/main.c libft.a -o lexer.out
	$(VALGRIND) ./lexer.out
	rm -f lexer.out

parser:
	$(COMPILE) $(SYSTEM) $(LEXER) $(PARSER) 2_test/main.c libft.a -o parser.out
	$(VALGRIND) ./parser.out
	rm -f parser.out

env:
	$(COMPILE) $(SYSTEM) $(ENV) 5_test/__main_env.c libft.a -o env.out
	$(VALGRIND) ./env.out
	rm -f env.out

path:
	$(COMPILE) $(SYSTEM) $(ENV) 5_test/__main_path.c libft.a -o path.out
	$(VALGRIND) ./path.out
	rm -f path.out

var:
	$(COMPILE) $(SYSTEM) $(LEXER) $(ENV) 5_test/__main_var.c libft.a -o var.out
	$(VALGRIND) ./var.out
	rm -f var.out

redirect:
	$(COMPILE) $(SYSTEM) $(LEXER) $(REDIRECT) 4_test/main.c libft.a -o redirect.out
	$(VALGRIND) ./redirect.out
	rm -f redirect.out

exec:
	$(COMPILE) $(SYSTEM) $(LEXER) $(PARSER) $(ENV) $(EXECUTOR) $(REDIRECT) $(BUILTIN) 3_test/main.c libft.a $(LFLAGS) -o exec.out
	$(VALGRIND) ./exec.out
	rm -f exec.out

