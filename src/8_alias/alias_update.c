#include "ft_alias.h"
#include "ft_system.h"

t_status	alias_update(const char *file, t_info *info)
{
	int fd;
	// char absolute_path[PATH_MAX];
	// char rcfile_path[PATH_MAX];
	// t_list *parse_result;

	// todo path_dispatcher(absolute_path);
	if (!ft_strcmp(file, RCFILE))
		fd = open(file, O_RDONLY | O_CREAT);
	else
		fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf(2, "minishell: %s: %s\n", file, strerror(errno)),
			E_FILE);
	// parse_result = parse_rcfile(fd);
	ft_lstclear(&info->alias_map, free);
	info->alias_map = parse_alias_file(fd);
	return (info->status);
}