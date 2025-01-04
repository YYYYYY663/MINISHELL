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



SYSTEM      := ../src/0_system


system:
	$(CC) $(IFLAGS) $(CFLAGS) $(DFLAGS) $(LFLAGS) $(SYSTEM)/*.c 0_test/system_main.c libft.a -o system.out
	$(VALGRIND) ./system.out
	rm -f system.out

	

