#include "ft_parser.h"

t_status	launch_parser(t_info *info)
{
#ifdef FUNC_OUT
	printf("%s\n", __func__);
#endif
	info->ast = expr(&info->token_list, info);
#ifdef FUNC_OUT
	printf("%s done\n", __func__);
#endif
	return (E_NONE);
}
