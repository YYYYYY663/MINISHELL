

#include "ft_redirect.h"
#include "xunistd.h"

int heredoc(const char *delimiter, t_info *info)
{
    int pipefds[2];
    xpipe(pipefds, info);

    //ctrol Dでも終了
    //ctrol C
    char *line;
    while(1)
    {
        printf(">");
        fflush(stdout);
        line = get_next_line(STDIN_FILENO);
        if (ft_strncmp(line, delimiter, ft_strlen(line)-1) == 0)
        {
            free(line);
            break;
        }
        write(pipefds[1], line, ft_strlen(line));
        free(line);
    }
    xclose(&pipefds[1]);
    return (pipefds[0]);
}