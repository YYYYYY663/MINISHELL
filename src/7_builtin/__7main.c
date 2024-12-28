#include "ft_builtin.h"
#include "ft_env.h"
#include "ft_system.h"
#include <unistd.h>

// /******  348e5933-7df0-4264-be7e-837938e8b1b2  *******/
int	main(int argc, char const **argv, char **env)
{
	t_info		*info;
	static char	*av[5] = {"echo", "abc", "def", NULL};
	static char	*av1[5] = {"cd", "-", NULL};
	static char	*av4[5] = {"unset", "SAMPLE_KEY2", NULL};
	static char	*av2[5] = {"export", "SAMPLE_KEY=AIOUE", NULL};
	static char	*av3[5] = {"export", "SAMPLE_KEY2=TSET", NULL};

	info = system_init(env);
	// builtin_dispatcher("echo", av, info);
	// printf("SAMPLE_KEY %s\n", env_get(info->env_map, "SAMPLE_KEY"));
	// printf("SAMPLE_KEY2 %s\n", env_get(info->env_map, "SAMPLE_KEY2"));
	// builtin_dispatcher("export", av2, info);
	// printf("SAMPLE_KEY %s\n", env_get(info->env_map, "SAMPLE_KEY"));
	// builtin_dispatcher("export", av2, info);
	// builtin_dispatcher("export", av3, info);
	// // builtin_dispatcher("env", NULL, info);
	// builtin_dispatcher("unset", av1, info);
	// // builtin_dispatcher("unset", av4, info);
	// printf("SAMPLE_KEY %s\n", env_get(info->env_map, "SAMPLE_KEY"));
	// printf("SAMPLE_KEY2 %s\n", env_get(info->env_map, "SAMPLE_KEY2"));
	// env_unset("OLDPWD",info);
	printf("%s\n",env_get("OLDPWD", info));
	builtin_dispatcher("pwd", av, info);
	builtin_dispatcher("cd", av1, info);
	builtin_dispatcher("pwd", av, info);
	printf("%s\n",env_get("OLDPWD", info));
	//builtin_dispatcher("env", av, info);
	//builtin_dispatcher("exit", NULL, info);
	system_exit(info,0);
	return (0);
}
