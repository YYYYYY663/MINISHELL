#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"


static void _display_sorted_env_line(const char *entity);
static void _display_sorted_env(t_info *info);

t_status	__export(const char *path, char **argv, t_info *info)
{
	int	i;

	#ifdef FUNC_OUT
	    printf("%s\n",__func__);
		ft_putstrs_endl_fd(argv,"  ",1);
    #endif
	i = 1;
	if (!argv[1])
	{
		_display_sorted_env(info);
	}
	while (argv[i])
	{
	
		env_export(argv[i++],info);
	}
	return (E_NONE);
}



static void _display_sorted_env(t_info *info)
{
	char **envp = ft_list_to_strs(info->env_map);
	int len = ft_list_size(info->env_map);
	int i;
	int j;
	i = 0;
	while (i < len -1)
	{
		j = i + 1;
        while (j < len)
        {
            if (ft_strcmp(envp[i], envp[j]) > 0)
            {
                ft_swap(envp[i], envp[j]);
            }
            j++;
        }
         _display_sorted_env_line(envp[i++]);
	}
	_display_sorted_env_line(envp[i++]);
}

static void _display_sorted_env_line(const char *entity)
{
	char    *key;
    char    *value;

	key = ft_substr_l(entity,'=');
	value = ft_substr_r(entity,'=');

    ft_putstr_fd("declare -x " ,STDOUT_FILENO);
	ft_putstr_fd(key,STDOUT_FILENO);
	if (value[0])
	{
		ft_putstr_fd("=\"",STDOUT_FILENO);
        ft_putstr_fd(value,STDOUT_FILENO);
		ft_putstr_fd("\"",STDOUT_FILENO);
	}
	printf("\n");
	free(value);
	free(key);
}




