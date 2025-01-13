#include "mish_alias.h"

// int	_check_key(char *key)
// {
// 	int	i;

// 	if (!ft_isalpha(key[0]) && key[0] != '_')
// 	{
// 		ft_dprintf(STDERR_FILENO,
// 			"minishell: export: `%s\': not a valid identifier\n", key);
// 		return (1);
// 	}
// 	i = 0;
// 	while (key[++i])
// 	{
// 		if (!ft_isalnum(key[i]) && key[i] != '_')
// 		{
// 			ft_dprintf(STDERR_FILENO,
// 				"minishell: export: `%s\': not a valid identifier\n", key);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

bool _validate_key(int index, const char *key)
{
    //keyに無効な文字が入っている、、、
    //valueが二単語
    //quoteが閉じられていない
    if (0)
        ft_dprintf(2,"minishell: %d: %s\n",index,"error msg");
    return true;
}
bool _validate_value(int index, const char *value)
{
    //keyに無効な文字が入っている、、、
    //valueが二単語
    //quoteが閉じられていない
    if (0)
        ft_dprintf(2,"minishell: %d: %s\n",index,"error msg");
    return true;
}


t_lmap *parse_rcfile(int fd)
{
    char *line;
    t_lmap *lmap = NULL;
    line = get_next_line(fd);
    int index = 1;
    while(!line)
    {
        if (!ft_strcmp("alias ", line))
        {
            char *key = ft_substr_l(line + ft_strlen("alias "), '=');
            char *value = ft_substr_r(line + ft_strlen("alias "), '=');
            if (_validate_key(index,key) && _validate(index,value))
                lmap_export(key,value,lmap,NULL);
            free(key);
            free(value);
        }
        free(line);
        line = get_next_line(fd);
        index++;
    }
    free(line);
    return lst;
}