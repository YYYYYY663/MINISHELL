#include "ft_parser.h"

t_status	launch_parser(t_info *info)
{
	t_list	*head;

	head = info->token_list;
	info->ast = expr(&head, info);
	return (E_NONE);
}
