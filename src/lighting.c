#include "../inc/rtv1.h"

int 	ft_color_to_int(t_color color)
{
	color.rgb.x = color.rgb.x >= 255 ? 255 : color.rgb.x;
	color.rgb.y = color.rgb.y >= 255 ? 255 : color.rgb.y;
	color.rgb.z = color.rgb.z >= 255 ? 255 : color.rgb.z;
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
			&& objs->t < 0.75 && objs->t > 0.01)
			return (1);
		objs = objs->next;
	}
	return (0);
}

float		ft_shine(t_object *obj,	t_vector3d point_to_light,
		t_vector3d dir, t_light *light)
{
	float		normal_to_light;
	t_vector3d	vector_to_light;
	float		shine_intensity;		

	shine_intensity = 0;
	point_to_light = ft_normalize(point_to_light);
	vector_to_light = ft_dif(
		ft_vector_product_number(obj->normal, ft_dot(obj->normal, point_to_light) * 2),
		point_to_light);
	vector_to_light = ft_normalize(vector_to_light);
	normal_to_light = ft_dot(vector_to_light, dir);
	if (normal_to_light > 0)
		shine_intensity = light->intensity * normal_to_light /
			(ft_length(vector_to_light) * ft_length(dir));
	return (shine_intensity);
}

int		ft_ray_to_light(t_rtv1 *rtv1, t_object *obj, t_vector3d dir)
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
				{
					total_intensity += light->intensity * n / (ft_length(obj->normal)
						* ft_length(point_to_light));
					total_intensity += ft_shine(obj, point_to_light,
						ft_vector_product_number(dir, -1), light);
				}
			}
		}
		light = light->next;
	}
	color.rgb = ft_vector_product_number(obj->color.rgb, total_intensity);
	return (ft_color_to_int(color));
}