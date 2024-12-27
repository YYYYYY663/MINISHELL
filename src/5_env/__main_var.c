


#include "ft_system.h"
#include "ft_env.h"

int	main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
	t_info	*info;
	info = system_init(envp);

   
    
	system_exit(info, 0);
}
