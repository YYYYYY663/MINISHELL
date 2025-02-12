/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 04:10:42 by teando            #+#    #+#             */
/*   Updated: 2025/02/12 19:07:13 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

#define METACHARS "|&;()<> \t\n"
#define IFS " \t\n"

t_token	*consume_word(char **linep, t_status *status)
{
	size_t	len;
	char	*line;

	(void)status;
	line = *linep;
	len = 0;
	while (line[len] && !ft_strchr(METACHARS, line[len]))
	{
		if (line[len] == '"')
			while (line[++len] && line[len] != '"')
				;
		else if (line[len] == '\'')
			while (line[++len] && line[len] != '\'')
				;
		len++;
	}
	*linep += len;
	return (token_new(TT_WORD, ft_strndup(line, len)));
}

t_token_type	identify_redirect(char **line, t_status *status)
{
	if (!ft_strncmp(*line, ">>", 2))
	{
		(*line) += 2;
		return (TT_APPEND);
	}
	if (!ft_strncmp(*line, "<<", 2))
	{
		(*line) += 2;
		return (TT_HEREDOC);
	}
	if (**line == '<')
	{
		(*line)++;
		return (TT_REDIR_IN);
	}
	(*line)++;
	return (TT_REDIR_OUT);
}

/**
 * @return next token's type
 */
t_token_type	consume_ifs(char **line, t_status *status)
{
	(void)status;
	while (**line && ft_strchr(IFS, **line))
		(*line)++;
	if (**line == '\0')
		return (TT_EOF);
	if (ft_strchr(METACHARS, **line))
		return (TT_NOTWORD);
	return (TT_WORD);
}

t_token	*consume_redirect(char **line, t_status *status)
{
	t_token_type	type;
	t_token			*token;

	type = identify_redirect(line, status);
	if (consume_ifs(line, status) != TT_WORD)
	{
		*status = E_SYNTAX;
		ft_dprintf(2, "minishell: syntax error near unexpected token `%c'\n",
			**line);
		return (NULL);
	}
	token = consume_word(line, status);
	token->type = type;
	return (token);
}
t_token	*consume_connector(char **line, t_status *status)
{
	t_token	*token;

	token = NULL;
	if (!ft_strncmp(*line, "&&", 2))
	{
		(*line)++;
		token = token_new(TT_AND_AND, NULL);
	}
	else if (!ft_strncmp(*line, "||", 2))
	{
		(*line)++;
		token = token_new(TT_OR_OR, NULL);
	}
	else if (**line == '|')
		token = token_new(TT_PIPE, NULL);
	else if (**line == ';')
		token = token_new(TT_SEMICOLON, NULL);
	else if (**line == '&')
	{
		ft_dprintf(2, "ERROR: sorry we don't manage background jobs :(\n");
		*status = E_SYNTAX;
		return (NULL);
	}
	(*line)++;
	if (consume_ifs(line, status) != TT_WORD)
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `%c'\n",
			**line);
		*status = E_SYNTAX;
	}
	return (token);
}

t_token	*consume_metachars(char **line, t_status *status)
{
	t_token	*token;

	if (ft_strchr(IFS, **line))
		return ((*line)++, NULL);
	if (**line == '<' || **line == '>')
		return (consume_redirect(line, status));
	if (**line == '&' || **line == '|' || **line == ';')
		return (consume_connector(line, status));
	if (**line == '(')
	{
		(*line)++;
		return (token_new(TT_LPAREN, NULL));
	}
	else
	{
		(*line)++;
		return (token_new(TT_RPAREN, NULL));
	}
}

t_list	*tokenize_line(char *line, t_status *status)
{
	t_list	*lst;
	t_token	*token;

	lst = NULL;
	if (ft_strchr("|&;)", *line))
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `%c'\n",
			*line);
		*status = E_SYNTAX;
		return (NULL);
	}
	while (*line)
	{
		if (ft_strchr(METACHARS, *line))
			token = consume_metachars(&line, status);
		else
			token = consume_word(&line, status);
		if (token)
			ft_lstadd_back(&lst, ft_lstnew(token));
		if (*status)
			return (ft_lstclear(&lst, token_clear), NULL);
	}
	ft_lstadd_back(&lst, ft_lstnew(token_new(TT_EOF, NULL)));
	return (lst);
}

t_status	launch_lexer(t_info *info)
{
	if (!info->line)
		return (E_SYNTAX);
	info->token = tokenize_line(info->line, &info->status);
	add_history(info->line);
	return (info->status);
}
