#include "../inc/rtv1.h"

void	ft_parse(int fd, t_rtv1 *rtv1)
{
	char	*line;
	char	*title;
	int		i;

	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (ft_strchr(line, ':'))
		{
			while (line[i] != ':')
				i++;
			if (i <= 0 || i > 10 || (line[i + 1] && line[i + 1] != '\0'))
				ft_exit(rtv1, 1, "Parse error: bad line");
			title = (char *)malloc(sizeof(char) * (i + 1));
			title[i] = '\0';
			while (--i >= 0)
				title[i] = line[i];
			ft_strdel(&line);
			if (!ft_strcmp(title, "camera"))
			{
				ft_strdel(&title);
				ft_parse_camera_data(fd, rtv1);
			}
			/*else if (!ft_strcmp(title, "light"))
			{
				ft_strdel(&title);
				ft_parse_light_data(fd, rtv1)
			}
			else if (!ft_strcmp(title, "sphere"))
			{
				ft_strdel(&title);
				ft_parse_sphere_data(fd, rtv1)
			}
			else if (!ft_strcmp(title, "plane"))
			{
				ft_strdel(&title);
				ft_parse_plane_data(fd, rtv1)
			}	
			else if (!ft_strcmp(title, "cylinder"))
			{
				ft_strdel(&title);
				ft_parse_cylinder_data(fd, rtv1)
			}	
			else if (!ft_strcmp(title, "cone"))
			{
				ft_strdel(&title);
				ft_parse_cone_data(fd, rtv1)
			}*/
			else
				ft_exit(rtv1, 1, "Parse error: bad line");		
		}
		else
			ft_exit(rtv1, 1, "Parse error: bad line");
	}
}

void		ft_skip_breckets(int fd, t_rtv1 *rtv1, int is_open)
{
	char *line;

	if (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, is_open == 1 ? "{" : "}"))
			ft_exit(rtv1, 1, "Parse error: bad line");
	}
	else
		ft_exit(rtv1, 1, "Parse error: bad line");
}

t_vector3d	ft_parse_get_vector_param2(t_rtv1 *rtv1, char *line)
{
	t_vector3d	param;
	int			i;
	int			j;
	int			number_indexes[3];

	i = 0;
	while (line[i] != ':')
		i++;
	i++;
	if (line[i++] != ' ')
		ft_exit(rtv1, 1, "Parse error: bad line");
	j = -1;
	if (ft_isdigit(line[i]) || (line[i] == '-' && line[i + 1] && ft_isdigit(line[i + 1])))
		number_indexes[++j] = i;
	else
		ft_exit(rtv1, 1, "Parse error: bad line");
	if (line[i] == '-')
		i++;
	while (ft_isdigit(line[i]) && j < 3)
	{
		if (line[i + 1] && line[i + 2] && line[i + 1] == ',' && line[i + 2] == ' ')
		{
			i += 3;
			if (ft_isdigit(line[i]) || (line[i] == '-' && line[i + 1] && ft_isdigit(line[i + 1])))
				number_indexes[++j] = i;
			else
				ft_exit(rtv1, 1, "Parse error: bad line");
			if (line[i] == '-')
				i++;
		}
		else
			i++;
	}
	if (j != 2 || line[i] != '\0')
		ft_exit(rtv1, 1, "Parse error: bad line");
	param.x = ft_atoi(line + number_indexes[0]);
	param.y = ft_atoi(line + number_indexes[1]);
	param.z = ft_atoi(line + number_indexes[2]);
	ft_strdel(&line);
	return (param);
}

t_vector3d	ft_parse_get_vector_param(int fd, t_rtv1 *rtv1, char *param_name)
{
	char		*line;
	char		*param_line;
	int			i;

	if (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (!ft_strchr(line, ':'))
			ft_exit(rtv1, 1, "Parse error: bad line");
		if (line[i++] != '\t')
			ft_exit(rtv1, 1, "Parse error: bad line");
		while (line[i] != ':')
			i++;
		param_line = (char *)malloc(sizeof(char) * (i + 1));
		param_line[i] = '\0';
		while (--i >= 0)
			param_line[i] = line[i];
		if (ft_strcmp(param_line, param_name))
			ft_exit(rtv1, 1, "Parse error: bad line");
	}
	else
		ft_exit(rtv1, 1, "Parse error: bad line");
	return (ft_parse_get_vector_param2(rtv1, line));
}

/*float	ft_parse_get_scalar_param(int fd, t_rtv1 *rtv1, char *param_name)
{
	return (0);
}*/

void	ft_parse_camera_data(int fd, t_rtv1 *rtv1)
{
	t_vector3d	location;
	t_vector3d	rotation;

	ft_skip_breckets(fd, rtv1, 1);
	location = ft_parse_get_vector_param(fd, rtv1, "\tlocation");
	rotation = ft_parse_get_vector_param(fd, rtv1, "\trotation");
	ft_skip_breckets(fd, rtv1, 0);
	rtv1->camera = ft_camera_constructor(location, rotation);
	ft_printf("camera location = %f %f %f \n", rtv1->camera->location.x,
		rtv1->camera->location.y, rtv1->camera->location.z);
	ft_printf("camera rotation = %f %f %f \n", rtv1->camera->rotation.x,
		rtv1->camera->rotation.y, rtv1->camera->rotation.z);
}