#include "../inc/rtv1.h"

void	ft_parse(int fd, t_rtv1 *rtv1)
{
	char *line;

	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line); 
	}
}