#include "mish_stream.h"

char	*launch_readline(const char *prompt)
{
	char	*line;
	char	*tmp;
	char	*cont_line;

	line = read_command_line(prompt);
	if (!line)
		return (NULL);
	while (!is_quotes_balanced(line))
	{
		if (g_signal_status == SIGINT)
			return (NULL);
		cont_line = read_command_line("> ");
		if (!cont_line)
			return (free(line), NULL);
		tmp = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin_free(tmp, cont_line);
		if (!line)
			return (NULL);
	}
	return (line);
}
