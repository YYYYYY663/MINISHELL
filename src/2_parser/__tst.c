#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "ft_token.h"

const char *generate_random_value(t_token_type type)
{
    switch (type)
    {
    case TT_WORD:
        return "random_word";
    case TT_PIPE:
        return "|";
    case TT_REDIR_IN:
        return "<";
    case TT_APPEND:
        return ">>";
    case TT_REDIR_OUT:
        return ">";
    case TT_HEREDOC:
        return "<<";
    case TT_LPAREN:
        return "(";
    case TT_RPAREN:
        return ")";
    case TT_AND_AND:
        return "&&";
    case TT_OR_OR:
        return "||";
    case TT_SEMICOLON:
        return ";";
    case TT_EOF:
        return "EOF";
    case TT_ERROR:
        return "ERROR";
    default:
        return "unknown";
    }
}

// トークンを作成する関数
t_token *create_token(t_token_type type)
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;

    new_token->type = type;
    new_token->value = strdup(generate_random_value(type));  // value をコピー
    return new_token;
}

// リストに新しい要素を追加する関数
void ft_list_add_back(t_list **list, t_token *token)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
        return;

    new_node->data = token;
    new_node->next = NULL;

    if (*list == NULL)
    {
        *list = new_node;
    }
    else
    {
        t_list *temp = *list;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

// メモリを解放する関数
void free_list(t_list *list)
{
    t_list *temp;
    while (list)
    {
        temp = list;
        list = list->next;
        free(((t_token *)temp->data)->value);
        free(temp->data);
        free(temp);
    }
}

// ランダムなトークンを生成してリストに追加する関数
void generate_random_tokens(t_list **list, int num_tokens)
{
    srand(time(NULL));

    for (int i = 0; i < num_tokens; i++)
    {
        t_token_type random_type = rand() % 12;  // 12種類のトークンタイプからランダムに選ぶ
        t_token *new_token = create_token(random_type);
        if (new_token)
        {
            ft_list_add_back(list, new_token);
        }
    }
}

// リストの内容を表示する関数
void print_tokens(t_list *list)
{
    t_list *temp = list;
    while (temp)
    {
        t_token *token = (t_token *)temp->data;
        printf("Token type: %d, value: %s\n", token->type, token->value);
        temp = temp->next;
    }
}

int main()
{
    t_list *token_list = NULL;

    // ランダムなトークンを10個生成してリストに追加
    generate_random_tokens(&token_list, 10);

    // トークンリストの内容を表示
    print_tokens(token_list);

    // メモリを解放
    free_list(token_list);

    return 0;
}
