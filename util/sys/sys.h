#ifndef SYSTEM_H
#define SYSTEM_H

# include "libft.h"
#include "lmap.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
#include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include  <string.h>

# ifndef PATH_MAX
#  define PATH_MAX 2048
# endif

typedef enum e_status
{
	E_NONE = 0,
	E_ALLOCATE = 1,
	E_ENV_KEY = 1,
	E_SYNTAX = 1,
	E_PIPE = 1,
	E_FILE,
	E_ARGUMENT,
	E_NOT_BUITIN_CMD = -2,
	E_COMMAND_NOT_FOUND = 127,
	E_SIGINT = 130,
	E_SIGQUIT = 131,
}								t_status;


/* -------------------------------------------------------------------------- */
/*                                   STRUCT                                   */
/* -------------------------------------------------------------------------- */

typedef struct s_ast t_ast;

typedef struct s_info
{
	char						*source_line;
	t_list						*token_list;
	t_ast						*ast;
	t_lmap						*env_map;
	char						*env_spc[128];
	t_lmap						*alias;
	int							stdfile_backup[2];
	char						cwd[PATH_MAX];
	char						home[PATH_MAX];
	t_status					status;
}								t_info;

/* -------------------------------------------------------------------------- */
/*                                   FUNCS                                    */
/* -------------------------------------------------------------------------- */
t_info							*system_init(char **envp);
void							line_init(t_info *info);
void							system_exit(t_info *info, t_status status);


#endif