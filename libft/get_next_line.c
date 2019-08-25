/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantropo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 09:13:24 by aantropo          #+#    #+#             */
/*   Updated: 2018/11/02 14:56:39 by aantropo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_insert(char **line, char *tmp)
{
	char *s;

	if (!(*line))
		*line = ft_strdup(tmp);
	else
	{
		s = *line;
		*line = ft_strjoin(*line, tmp);
		ft_strdel(&s);
	}
}

void	ft_fill_line(char *tmp_line, char **line)
{
	char	*sub;
	int		i;

	i = 0;
	while (tmp_line[i] != '\n')
		i++;
	sub = ft_strnew(i);
	i = -1;
	while (tmp_line[++i] != '\n')
		sub[i] = tmp_line[i];
	sub[i] = '\0';
	ft_insert(line, sub);
	free(sub);
	i = ft_strchr(tmp_line, '\n') - tmp_line;
	ft_memmove(tmp_line, &tmp_line[i + 1], BUFF_SIZE);
}

void	ft_func(char *tmp_line, char *buff, char **line)
{
	ft_strcat(tmp_line, buff);
	ft_insert(line, tmp_line);
	ft_strclr(buff);
	ft_strclr(tmp_line);
}

int		ft_loop(char **line, char *tmp_line, char *buff, int fd)
{
	int		i;

	while ((i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[i] = '\0';
		if (ft_strchr(buff, '\n'))
		{
			ft_strcat(tmp_line, buff);
			ft_fill_line(tmp_line, line);
			ft_strclr(buff);
			i = 1;
			break ;
		}
		else if (ft_strlen(tmp_line) > 0 && ft_strlen(buff) < BUFF_SIZE)
		{
			ft_func(tmp_line, buff, line);
			i = 1;
			break ;
		}
		else if (ft_strlen(tmp_line) > 0)
			ft_func(tmp_line, buff, line);
		ft_insert(line, buff);
		ft_strclr(buff);
	}
	return (i);
}

int		get_next_line(const int fd, char **line)
{
	static char	tmp_line[4864][BUFF_SIZE + 1];
	char		buff[BUFF_SIZE + 1];
	int			i;

	if (fd < 0 || fd > 4863)
		return (-1);
	*line = (char *)malloc(1);
	ft_strclr(*line);
	if (ft_strchr(tmp_line[fd], '\n'))
	{
		ft_fill_line(tmp_line[fd], line);
		return (1);
	}
	if ((i = ft_loop(line, tmp_line[fd], buff, fd)) != 0)
		return (i);
	if (ft_strlen(tmp_line[fd]) > 0 && ft_strchr(tmp_line[fd], '\0'))
	{
		ft_insert(line, tmp_line[fd]);
		ft_strclr(tmp_line[fd]);
		return (1);
	}
	if (**line)
		return (1);
	return (0);
}
