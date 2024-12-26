/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:33:27 by ymizukam          #+#    #+#             */
/*   Updated: 2024/12/22 16:33:29 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_system.h"
#include "ft_token.h"

void token_clear(void *ptr)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	t_token *token = (t_token *)ptr; 
	if (!token)
        return ;
    free(token->value);
    free(token);
}

void	ast_clear(t_ast *node)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	if (!node)
		return ;
	ast_clear(node->left);
	ast_clear(node->right);
	if (node->args)
	{
		ft_lstclear(&node->args,token_clear);
	}
	free(node);
}

t_info *system_init(char **envp)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	t_info *info;

	info = ft_calloc(sizeof(t_info), 1);
	if (!info)
		return (NULL);
	(void)envp;
	info->env_map = ft_list_from_strs(envp);
	if(getcwd(info->cwd, PATH_MAX))
		//todo 
		;
	return (info);
}

void system_deinit(t_info *info)
{
	#ifdef FUNC_OUT
		printf("%s\n",__func__);
	#endif
	if (!info)
		return;
	free(info->source_line);
	if (info->token_list != NULL)
	{
		//ft_lstclear(&info->token_list, &token_clear);でも動く。。。謎
		ft_lstclear(&info->token_list, token_clear);
	}
	if (info->env_map != NULL)
		ft_lstclear(&info->env_map, free);
	ast_clear(info->ast);
	free(info);
}
