#include "../inc/rtv1.h"

static int	ft_parse_get_vector_param3(char *l, int i, t_vector3d *param)
{
	if (ft_isdigit(l[i]) || (l[i] == '-' && l[i + 1] && ft_isdigit(l[i + 1])))
		param->x = ft_atoi(l + i);
	else
		return (0);
	i = l[i] == '-' ? i + 1 : i;
	while (ft_isdigit(l[i]))
		i++;
	if (l[i++] != ' ')
		return (0);
	if (ft_isdigit(l[i]) || (l[i] == '-' && l[i + 1] && ft_isdigit(l[i + 1])))
		param->y = ft_atoi(l + i);
	else
		return (0);
	i = l[i] == '-' ? i + 1 : i;
	while (ft_isdigit(l[i]))
		i++;
	if (l[i++] != ' ')
		return (0);
	if (ft_isdigit(l[i]) || (l[i] == '-' && l[i + 1] && ft_isdigit(l[i + 1])))
		param->z = ft_atoi(l + i);
	else
		return (0);
	i = l[i] == '-' ? i + 1 : i;
	return (i);
}

static int		ft_parse_get_vector_param2(t_vector3d *param, char *line)
{
	int			i;

	i = 0;
	while (line[i] != ':')
		i++;
	i++;
	if (line[i++] != ' ')
		return (0);
	i = ft_parse_get_vector_param3(line, i, param);
	if (!i)
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	return (line[i] == '\0' ? 1 : 0);
}

int	ft_parse_get_vector_param(int fd, t_vector3d *param, char *param_name)
{
	char		*line;
	char		*param_line;
	int			i;

	if (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (!ft_strchr(line, ':'))
		{
			ft_strdel(&line);
			return (0);
		}
		if (line[i++] != '\t')
		{
			ft_strdel(&line);
			return (0);
		}
		while (line[i] != ':')
			i++;
		param_line = (char *)malloc(sizeof(char) * (i + 1));
		param_line[i] = '\0';
		while (--i >= 0)
			param_line[i] = line[i];
		if (ft_strcmp(param_line, param_name))
		{
			ft_strdel(&line);
			ft_strdel(&param_line);
			return (0);
		}
	}
	else
	{
		ft_strdel(&line);
		return (0);
	}
	ft_strdel(&param_line);
	if (!ft_parse_get_vector_param2(param, line))
		return (0);
	return (1);
}

static float	ft_parse_get_scalar_param2(t_rtv1 *rtv1, char *line, int i)
{
	float 		param;

	if (line[i++] != ' ')
		ft_exit(rtv1, 1, "Parse error: bad line");
	if (line[i] && (ft_isdigit(line[i]) || (line[i] == '-' && line[i + 1]
		&& ft_isdigit(line[i + 1]))))
		param = ft_atoi(line + i);
	else
		ft_exit(rtv1, 1, "Parse error: bad line");
	if (line[i] == '-')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
		ft_exit(rtv1, 1, "Parse error: bad line");
	return(param);
}

float	ft_parse_get_scalar_param(int fd, t_rtv1 *rtv1, char *param_name)
{
	float 		param;	
	char		*line;
	char		*param_line;
	int			i;

	if (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (!ft_strchr(line, ':') || line[i++] != '\t')
			ft_exit(rtv1, 1, "Parse error: bad line");
		while (line[i] != ':')
			i++;
		param_line = (char *)malloc(sizeof(char) * (i + 1));
		param_line[i] = '\0';
		while (--i >= 0)
			param_line[i] = line[i];
		if (ft_strcmp(param_line, param_name))
		{
			ft_strdel(&param_line);
			ft_exit(rtv1, 1, "Parse error: bad line");
		}
		while (line[i] != ':')
			i++;
		i++;
		ft_strdel(&param_line);
		param = ft_parse_get_scalar_param2(rtv1, line, i);
		ft_strdel(&line);
	}
	return (param);
}