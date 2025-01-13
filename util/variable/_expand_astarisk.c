/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _var_expand_astarisk.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 04:52:54 by teando            #+#    #+#             */
/*   Updated: 2025/01/09 05:02:51 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <dirent.h>
#include <errno.h>
#include <string.h>
// #include "ft_system.h"
// #include "ft_lexer.h"
#include "variable.h"
#include "xunistd.h"

/**
 * @brief アスタリスク（*）によるグロブ展開を行う
 * 
 * この関数は以下の処理を行います：
 * 1. トークンが'*'の場合：
 *    - カレントディレクトリの内容を取得
 *    - 各エントリに対して新しいトークンを作成
 *    - 元のトークンを新しいトークンリストで置換
 * 2. トークンが'*'でない場合は何もしない
 * 
 * @param head トークンリストのヘッド
 * @param info シェル情報構造体
 * @return int 0:成功、-1:失敗
 */
int expand_astarisk(t_list **head, t_info *info)
{
    t_list *node;
    t_token *token;
    DIR *dir;
    struct dirent *entry;
    t_list *new_list;

    node = *head;
    token = (t_token *)node->data;
    if (ft_strcmp(token->value, "*") != 0)
        return (0);
    char *current_dir = env_get("PWD", info);
    if (!current_dir)
        current_dir = ".";
    dir = opendir(current_dir);
    if (!dir)
    {
        ft_dprintf(2, "expand_astarisk: opendir failed: %s\n", strerror(errno));
        return (0);
    }
    new_list = NULL;
    while ((entry = readdir(dir)) != NULL)
    {
        t_token *new_token;

        new_token = malloc(sizeof(t_token));
        if (!new_token)
        {
            closedir(dir);
            return (0);
        }
        new_token->type = TT_WORD;
        new_token->value = ft_strdup(entry->d_name);
        ft_lstadd_back(&new_list, ft_lstnew(new_token));
    }
    closedir(dir);
    ft_lstdelone(*head, token_clear);
    t_list *last;
    t_list *old_next;

    last = new_list;
    if (last)
    {
        while (last->next)
            last = last->next;
    }
    old_next = node->next;
    if (last)
        last->next = old_next;
    if (new_list)
        *head = new_list;
    else
        *head = old_next;
    (void)info;
    return (0);
}
