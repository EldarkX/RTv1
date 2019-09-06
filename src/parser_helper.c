#include "../inc/rtv1.h"

static int		ft_parse_get_vector_param2(char *l, int i, t_vector3d *param)
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

int				ft_parse_get_vector_param(int fd, t_vector3d *param, char *param_name, int i)
{
	char		*line;
	char		param_line[20];

	if (get_next_line(fd, &line) > 0)
	{
		i = !ft_strchr(line, ':') || !line[0] || line[0] != '\t' ? -1 : 0;
		if (i != -1)
		{
			fd = 0;
			while (line[i] && line[i] != ':' && fd < 19)
				param_line[fd++] = line[i++];
			param_line[fd] = '\0';
			i = (ft_strcmp(param_line, param_name) || !line[i + 1] ||
				line[i + 1] != ' ') ? -1 : i;
		}
	}
	if (i != -1)
		i = ft_parse_get_vector_param2(line, i + 2, param);
	if (i < 1)
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	i = line[i] == '\0' ? 1 : 0;
	ft_strdel(&line);
	return (i);
}

static int		ft_parse_get_scalar_param2(float *param, char *line, double digit, int i)
{
	while (line[i] != ':')
		i++;
	i++;
	if (line[i++] != ' ')
		return (0);
	if (line[i] && (ft_isdigit(line[i]) || (line[i] == '-' && line[i + 1]
		&& ft_isdigit(line[i + 1]))))
		*param = ft_atoi(line + i);
	else
		return (0);
	if ((ABS((int)*param)) > 1000)
		return (0);
	i = line[i] == '-' ? i + 1 : i;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] && line[i++] == '.')
	{
		while (line[i] && ft_isdigit(line[i]) && digit <= 100)
		{
			*param = *param + (line[i++] - '0') / digit;
			digit *= 10;
		}
	}
	return (line[i] == '\0' ? 1 : 0);
}

int				ft_parse_get_scalar_param(int fd, float *param, char *param_name, int i)
{
	char		*line;
	char		param_line[20];
	int			j;

	if (get_next_line(fd, &line) > 0)
	{
		i = !ft_strchr(line, ':') || !line[0] || line[0] != '\t' ? -1 : 0;
		if (i != -1)
		{
			j = 0;
			while (line[i] && line[i] != ':' && j < 19)
				param_line[j++] = line[i++];
			param_line[j] = '\0';
			i = ft_strcmp(param_line, param_name) ? -1 : i;
		}
	}
	if (i != -1)
		i = !ft_parse_get_scalar_param2(param, line, 10, i) ? -1 : 1;
	ft_strdel(&line);
	return (i != -1 ? 1 : 0);
}

int		ft_perse_get_light_type(int fd, float *param_value, char *param_name, int i)
{
	char	*line;
	char	param[20];

	*param_value = -1;
	if (get_next_line(fd, &line) > 0)
	{
		if (!ft_strchr(line, ':'))
			return (0);
		fd = 0;
		while (line[i] && line[i] != ':' && fd < 19)
			param[fd++] = line[i++];
		param[fd] = '\0';
		if (ft_strcmp(param, param_name) || line[++i] != ' ')
			return (0);
		fd = 0;
		while (line[++i] && line[i] != '\0' && fd < 19)
			param[fd++] = line[i];
		param[fd] = '\0';
		if (!ft_strcmp(param, "AMBIENT") && line[i] == '\0')
			*param_value = 0;
		else if (!ft_strcmp(param, "DIFFUSE") && line[i] == '\0')
			*param_value = 1;		
	}
	ft_strdel(&line);
	return (*param_value >= 0 ? 1 : 0);
}