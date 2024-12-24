#include "ft_lexer.h"
#include <stdio.h>
#include <stdlib.h>

static void	print_tokens(t_token *tokens)
{
	char	*type_str;

	for (int i = 0; tokens[i].type != TT_EOF && tokens[i].type != TT_ERROR; i++)
	{
		switch (tokens[i].type)
		{
		case TT_WORD:
			type_str = "WORD";
			break ;
		case TT_PIPE:
			type_str = "PIPE";
			break ;
		case TT_REDIR_IN:
			type_str = "REDIRECT_IN";
			break ;
		case TT_REDIR_OUT:
			type_str = "REDIRECT_OUT";
			break ;
		case TT_APPEND:
			type_str = "APPEND";
			break ;
		case TT_HEREDOC:
			type_str = "HEREDOC";
			break ;
		default:
			type_str = "UNKNOWN";
			break ;
		}
		printf("TOKEN: type=%s, value=%s\n", type_str,
			tokens[i].value ? tokens[i].value : "(null)");
	}
	if (tokens[0].type == TT_ERROR)
		printf("ERROR TOKEN DETECTED\n");
}

static void	test_lexer(const char *input)
{
	t_token	*tok;

	printf("Input: [%s]\n", input);
	tok = lexer(input);
	print_tokens(tok);
	free_tokens(tok);
	printf("----\n");
}

int	main(void)
{
	// [#2-1] 基本トークナイザテスト
	test_lexer("echo hello world");
	test_lexer("ls -l | grep txt");
	test_lexer("cat < infile > outfile");
	// [#2-2] クォート処理テスト
	test_lexer("echo 'hello world'");
	test_lexer("echo \"hello   world\"");
	test_lexer("echo 'unclosed string"); // 未閉クォート -> ERROR TOKEN
	// [#2-3] ユニットテストを網羅する追加テスト
	test_lexer("   "); // 空白のみ
	test_lexer("echo \"multi words   in quotes\" next");
	test_lexer("cat << EOF");
	test_lexer("echo 'a|b'");
	test_lexer("echo \"hello | grep\"");
	test_lexer("ls >> out.txt");
	return (0);
}
