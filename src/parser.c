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
			{
				ft_strdel(&line);
				ft_exit(rtv1, 1, "Parse error: bad line");
			}
			title = (char *)malloc(sizeof(char) * (i + 1));
			title[i] = '\0';
			while (--i >= 0)
				title[i] = line[i];
			ft_strdel(&line);
			if (!ft_strcmp(title, "camera") || 
				!ft_strcmp(title, "light") || 
				!ft_strcmp(title, "sphere") || 
				!ft_strcmp(title, "plane") || 
				!ft_strcmp(title, "cylinder") || 
				!ft_strcmp(title, "cone"))
			{
				ft_printf("figure is %s\n", title);
				if (!ft_parse_data(fd, rtv1, title))
				{
					ft_strdel(&title);
					ft_exit(rtv1, 1, "Parse error: bad line");
				}
				ft_strdel(&title);
			}
			else
			{
				ft_strdel(&title);
				ft_exit(rtv1, 1, "Parse error: bad line");		
			}
		}
		else
		{
			ft_strdel(&line);
			ft_exit(rtv1, 1, "Parse error: bad line");
		}
	}
}

static int		ft_skip_breckets(int fd, int is_open)
{
	char	*line;
	int		result;

	result = 1;
	if (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, is_open == 1 ? "{" : "}"))
			result = 0;
		ft_strdel(&line);
	}
	else
		result = 0;
	return (result);
}

void	ft_choose_constructor(t_rtv1 *rtv1, char *title, t_vector3d *v_params,
	float *f_params)
{
	if (!ft_strcmp(title, "camera"))
		rtv1->camera = ft_new_camera(v_params[0], v_params[1]);
	else if (!ft_strcmp(title, "sphere"))
		rtv1->objects = ft_add_obj(rtv1, ft_new_sphere(v_params[0],
			v_params[1], f_params[0], v_params[2]));
	else if (!ft_strcmp(title, "plane"))
		rtv1->objects = ft_add_obj(rtv1, ft_new_plane(v_params[0],
			v_params[1], v_params[2]));
	else if (!ft_strcmp(title, "cylinder"))
		rtv1->objects = ft_add_obj(rtv1, ft_new_cylinder(v_params[0],
			v_params[1], f_params[0], v_params[2]));		
	else if (!ft_strcmp(title, "cone"))
		rtv1->objects = ft_add_obj(rtv1, ft_new_cone(v_params[0],
			v_params[1], f_params[0], v_params[2]));		
	else
		rtv1->light_sources = ft_add_light(rtv1, ft_new_light(v_params[0],
			v_params[1], f_params[0], (int)f_params[1]));			
}

int	ft_parse_data(int fd, t_rtv1 *rtv1, char *title)
{
	t_vector3d		vector_params[3];
	float			float_params[2];

	if (!ft_skip_breckets(fd, 1))
		return (0);
	if (!ft_parse_get_vector_param(fd, &vector_params[0], "\tlocation", -1))
		return (0);

	ft_print_vector(vector_params[0], "location");

	if (!ft_parse_get_vector_param(fd, &vector_params[1], "\trotation", -1))
		return (0);

	ft_print_vector(vector_params[1], "rotation");

	if (!ft_strcmp(title, "sphere") || !ft_strcmp(title, "plane") ||
		!ft_strcmp(title, "cylinder") || !ft_strcmp(title, "cone"))
	{
		if (!ft_parse_get_vector_param(fd, &vector_params[2], "\tcolor", -1))
			return (0);

		ft_print_vector(vector_params[2], "color");

		if (!ft_strcmp(title, "cone"))
		{
			if (!ft_parse_get_scalar_param(fd, &float_params[0], "\tangle", -1))
				return (0);

			printf("angle = %f\n", float_params[0]);

		}
		else if (!ft_strcmp(title, "sphere") || !ft_strcmp(title, "cylinder"))
		{
			if (!ft_parse_get_scalar_param(fd, &float_params[0], "\tradius", -1))
				return (0);

			printf("radius = %f\n", float_params[0]);
			
		}
	}
	else if (!ft_strcmp(title, "light"))
	{
		if (!ft_parse_get_scalar_param(fd, &float_params[0], "\tintensity", -1))
			return (0);

		printf("intensity = %f\n", float_params[0]);
		
		if (!ft_perse_get_light_type(fd, &float_params[1], "\ttype", 0))
				return (0);

		printf("type = %f\n", float_params[1]);

	}
	if (!ft_skip_breckets(fd, 0))
		return (0);
	ft_choose_constructor(rtv1, title, vector_params, float_params);
	return (1);
}