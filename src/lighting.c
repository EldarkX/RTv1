#include "../inc/rtv1.h"

int 	ft_color_to_int(t_color color)
{
	return
		(
			((unsigned int)color.rgb.x << 16) | 
			((unsigned int)color.rgb.y << 8) |
			((unsigned int)color.rgb.z << 0)
		);
}

int		ft_is_shadow(t_rtv1 *rtv1, t_vector3d intersect_point,
						t_vector3d point_to_light)
{
	t_object *objs;

	objs = rtv1->objects;
	point_to_light = ft_normalize(point_to_light);
	while (objs != NULL)
	{
		if (objs->ft_intersect(objs, intersect_point,
			point_to_light, ft_dif(intersect_point, objs->location))
			&& objs->t < 1 && objs->t > 0.005)
			return (1);
		objs = objs->next;
	}
	return (0);
}

int		ft_shine(t_rtv1 *rtv1, t_vector3d intersect_point,
						t_vector3d point_to_light)
{
	t_object *objs;

	objs = rtv1->objects;
	point_to_light = ft_normalize(point_to_light);
	while (objs != NULL)
	{
		if (objs->ft_intersect(objs, intersect_point,
			point_to_light, ft_dif(intersect_point, objs->location))
			&& objs->t < 1 && objs->t > 0.005)
			return (1);
		objs = objs->next;
	}
	return (0);
}

int		ft_ray_to_light(t_rtv1 *rtv1, t_object *obj)
{
	t_color		color;
	t_light		*light;
	float		total_intensity;
	t_vector3d	point_to_light;
	float		n;

	total_intensity = 0;
	light = rtv1->light_sources;
	while (light)
	{
		if (light->type == AMBIENT)
			total_intensity += light->intensity;
		else
		{
			point_to_light = ft_dif(light->location, obj->intersect_point);
			if (!ft_is_shadow(rtv1, obj->intersect_point, point_to_light))
			{
				n = ft_dot(point_to_light, obj->normal);
				if (n > 0)
				total_intensity += light->intensity * n / (ft_length(obj->normal)
					* ft_length(point_to_light));
			}
		}
		light = light->next;
	}
	color.rgb = ft_vector_product_number(obj->color.rgb, total_intensity);
	return (ft_color_to_int(color));
}