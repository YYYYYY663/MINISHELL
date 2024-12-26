/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:52:24 by teando            #+#    #+#             */
/*   Updated: 2024/12/23 21:59:18 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
# include "ft_token.h"

const char	*e_type_to_str(int t)
{
	if (t == NT_CMD)
		return ("NT_CMD");
	if (t == NT_PIPE)
		return ("NT_PIPE");
	if (t == NT_PRIORITY)
		return ("NT_PRIORITY");
	if (t == NT_AND)
	    return ("NT_AND");
	if (t == NT_EOF)
		return ("NT_EOF");
	if (t == NT_OR)
		return ("NT_OR");
	return ("UNKNOWN");
}

void	debug_print_ast(t_ast *ast, int depth)
{
	t_list			*p;
	char			*word;

	if (!ast)
		return ;
	for (int i = 0; i < depth; i++)
		ft_dprintf(STDOUT_FILENO, "  ");
	if (!ast)
	{
		ft_dprintf(STDOUT_FILENO, "(null)\n");
		return ;
	}
	// 種別表示
	ft_dprintf(STDOUT_FILENO, "[%s]", e_type_to_str(ast->ntype));
	// NT_CMD の場合、argsを出力
	if (ast->ntype == NT_CMD && ast->args)
	{
		ft_dprintf(STDOUT_FILENO, " args=[");
		p = ast->args->cmd;
		while (p)
		{
			word = (char *)p->data;
			ft_dprintf(STDOUT_FILENO, "%s", word);
			p = p->next;
			if (p)
				ft_dprintf(STDOUT_FILENO, ", ");
		}
		// ft_dprintf(STDOUT_FILENO, "%s", " :in: ");
		// p = ast->args->rd_i;
		// while (p)
		// {
		// 	word = (char *)p->data;
		// 	ft_dprintf(STDOUT_FILENO, "%s", word);
		// 	p = p->next;
		// 	if (p)
		// 		ft_dprintf(STDOUT_FILENO, ", ");
		// }
		ft_dprintf(STDOUT_FILENO, "]");
	}
	ft_dprintf(STDOUT_FILENO, "\n");
	// 再帰
	debug_print_ast(ast->left, depth + 1);
	debug_print_ast(ast->right, depth + 1);
}
