#include "ft_alias.h"
#include "ft_env.h"
#include "ft_system.h"

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

bool	_validate_key(int index, const char *key)
{
	// keyに無効な文字が入っている、、、
	// valueが二単語
	// quoteが閉じられていない
	(void)key;
	if (0)
		ft_dprintf(2, "minishell: %d: %s\n", index, "error msg");
	return (true);
}
bool	_validate_value(int index, const char *value)
{
	// keyに無効な文字が入っている、、、
	// valueが二単語
	// quoteが閉じられていない
	(void)value;
	if (0)
		ft_dprintf(2, "minishell: %d: %s\n", index, "error msg");
	return (true);
}

static bool	_alias_export(int index, char *entity, t_list *lmap)
{
	char	*key;
	char	*value;
	bool	status;

	key = ft_substr_l(entity, '=');
	value = ft_substr_r(entity, '=');
	status = _validate_key(index, key) && _validate_value(index, value);
	if (status)
		map_export(entity, lmap);
	free(key);
	free(value);
	return (status);
}

t_list	*parse_alias_file(int fd)
{
	char *line;
	t_list *list = NULL;
	line = get_next_line(fd);
	int index = 1;
	while (!line)
	{
		if (!ft_strcmp("alias", line))
		{
			char *entity = line;
			while (ft_isspace(*entity))
				entity++;
			if (*entity && !_alias_export(index, entity, list))
				return (free(line), ft_lstclear(&list, free), NULL);
		}
		free(line);
		line = get_next_line(fd);
		index++;
	}
	free(line);
	return (list);
}