/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:28:16 by ymizukam          #+#    #+#             */
/*   Updated: 2025/02/12 19:07:20 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

#define MAX_ENV_NAME 128
#define ERR_MALLOC "Malloc error\n"
#define INIT_BUFFER_SIZE 128

static void	*malloc_safe(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
        ft_dprintf(2, ERR_MALLOC);
	return (ptr);
}

static size_t ft_strcpy(char *dest, char *src)
{
    size_t i;

    i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return(i);
}


// static void toggle_quotes(char c, int *in_single_quote, int *in_double_quote)
// {
//     if (c == '\'' && !(*in_double_quote))
//         *in_single_quote = !(*in_single_quote);
//     else if (c == '"' && !(*in_single_quote))
//         *in_double_quote = !(*in_double_quote);
// }

// 変数名を取得する関数
// static int get_var_length(const char *str)
// {
//     int len = 0;
//     while (str[len] && (isalnum(str[len]) || str[len] == '_'))
//         len++;
//     return len;
// }

// 環境変数の展開
static char *expand_variable(const char **value, t_info *info)
{
    char var_name[MAX_ENV_NAME]; // 環境変数名を一時的に格納
    size_t var_len;

    var_len = 0;
    (*value)++; // '$' をスキップ
    while ((*value)[var_len] && (ft_isalnum((*value)[var_len]) || (*value)[var_len] == '_'))
    {
        var_name[var_len] = (*value)[var_len];
        var_len++;
    }
    var_name[var_len] = '\0';
    *value += var_len; // 環境変数名の長さ分ポインタを進める
    return (ft_strdup2(env_get(var_name,info))); // 取得した文字列を動的確保して返す
}





// シングルクォートを処理
static char *process_single_quote(const char **value)
{
    const char *start; 
    size_t len;
    char *result;
    
    start = ++(*value);
    while (**value && **value != '\'')
        (*value)++;
    len = *value - start;
    result = malloc_safe(len + 1);
    if(!result)
        return(NULL);
    ft_strncpy(result, start, len);
    if (**value == '\'')
        (*value)++;
    return result;
}

// ダブルクォートを処理
static char *process_double_quote(const char **value, t_info *info)
{
    char buffer[4096]; // 一時バッファ
    char *buf_ptr;
    const char *start;
    char *result;

    buf_ptr = buffer;
    start = ++(*value); // 開始位置（" をスキップ）
    while (**value && **value != '"')
    {
        if (**value == '$') // 変数展開
        {
            result = expand_variable(value, info);
            buf_ptr += ft_strcpy(buf_ptr, result);
            free(result);
        }
        else
            *buf_ptr++ = *(*value)++;
    }
    if (**value == '"') // 閉じる " をスキップ
        (*value)++;
    *buf_ptr = '\0'; // 終端文字を追加
    return ft_strdup2(buffer); // 必要な分だけ `malloc` して返す
}



static char *get_ifs()
{
    const char *ifs;
    
    ifs= getenv("IFS");
    if(!ifs)
        return(" \t\n");
    else
        return(ifs);
}


// static char *process_no_quote(const char **value, t_info *info)
// {
//     const char *ifs;
//     size_t buffer_size = 128;
//     char *result;
//     char *ptr;

//     ifs = get_ifs();
//     result = malloc_safe(buffer_size);
//     if (!result)
//         return NULL;
//     ptr = result;
//     while (**value && !ft_strchr(ifs, **value))
//     {
//         if (**value == '$')
//         {
//             size_t expanded_len;
//             char *expanded = expand_variable(value, info, &expanded_len);
//             ptr = expand_and_copy(ptr, &result, &buffer_size, expanded);
//             free(expanded);
//         }
//         else
//             *ptr++ = *(*value)++;
//     }
//     *ptr = '\0';
//     return result;
// }


static char *expand_and_copy(char *result, char **expanded, size_t *new_len, const char *processed)
{
    size_t processed_len;
    size_t current_len;
    size_t total_len;

    processed_len = ft_strlen(processed);
    current_len = result - *expanded;
    total_len = current_len + processed_len + 1;
    if (total_len > *new_len)
    {
        *new_len = total_len * 2;  // 新しいサイズ（倍増）
        *expanded = realloc(*expanded, *new_len);
        if (!*expanded)
            return NULL;
        result = *expanded + current_len;
    }
    result += ft_strcpy(result, processed);
    return result;
}



static char *split_and_copy_tokens(char *expanded, char *ptr, char **result, size_t *buffer_size)
{
    char *start;
    char *ifs;

    start = expanded;
    ifs = get_ifs();
    while (*start)
    {
        if (ft_strchr(ifs, *start))
        {
            *start = '\0';
            ptr = expand_and_copy(ptr, result, buffer_size, expanded);
            expanded = start + 1;
            while (*expanded && ft_strchr(ifs, *expanded))
                expanded++;
            start = expanded;
        }
        else
            start++;
    }
    if (*expanded)
        ptr = expand_and_copy(ptr, result, buffer_size, expanded);
    return ptr;
}



static char *handle_variable_expansion(const char **value, char *ptr, char **result, t_info *info)
{
    char *expanded;
    size_t buffer_size;

    buffer_size = INIT_BUFFER_SIZE;
    expanded= expand_variable(value, info);
    if (!expanded)
        return ptr;
    ptr = split_and_copy_tokens(expanded, ptr, result, &buffer_size);
    free(expanded);
    return ptr;
}

static char *process_no_quote(const char **value, t_info *info)
{
    char *result;
    char *ptr;
    char *ifs;

    ifs = get_ifs();
    result = malloc_safe(INIT_BUFFER_SIZE);
    if (!result)
        return NULL;
    ptr = result;
    while (**value && !ft_strchr(ifs, **value))
    {
        if (**value == '$')
            ptr = handle_variable_expansion(value, ptr, &result, info);
        else
            *ptr++ = *(*value)++;
    }
    *ptr = '\0';
    return result;
}


static size_t get_expanded_length(const char *value)
{
    size_t len;
    int in_single_quote;
    int in_double_quote;

    len = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    while (*value)
    {
        if (*value == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (*value == '"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else
            len++;
        value++;
    }
    return len;
}



static char *process_value(const char **value, t_info *info)
{
    if (**value == '\'')
        return process_single_quote(value);
    else if (**value == '"')
        return process_double_quote(value, info);
    else
        return process_no_quote(value, info);
}


static char *apply_expansion(const char *value, t_info *info)
{
    size_t new_len;
    char *expanded; 
    char *result;
    char *processed;

    new_len = get_expanded_length(value);
    expanded= malloc_safe(new_len + 1);
    if (!expanded)
        return NULL;
    result = expanded;
    while (*value)
    {
        processed = process_value(&value, info);  
        if (processed) 
        {
            result = expand_and_copy(result, &expanded, &new_len, processed);
            free(processed);
            if (!result)  // メモリ確保失敗
                return(free(expanded), NULL);
        }
        else
            return(free(expanded), NULL);
    }
    *result = '\0';  // 最後にNULL終端を追加
    return expanded;
}




void expand_dollar(t_list **lst, t_info *info)
{
    t_token *token;
    char *new_value;

    token = (t_token *)(*lst)->data;
    new_value = apply_expansion(token->value, info);
    if (!new_value)
    {
        ft_dprintf(2, "ERROR: we failed to expand variable\n");
        return ;
    }
    free(token->value);
    token->value = new_value;
}
