cc -Wall -Wextra -Werror -o lexer_test ../src/1_tokenizer/tokenizer.c lexer_test.c -I../inc -I../lib/libft
./lexer_test
rm lexer_test