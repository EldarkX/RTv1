#include "../inc/rtv1.h"

int ft_color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) |
		(color.b << 0));
}

int ft_ray_tracing_proccess(t_rtv1 *rtv1, t_vector3d dir)
{

	t_object *objs = rtv1->objects;
	t_object *nearest_obj = NULL;
	float distance;
	float min_distance;
	int is_first = 1;
	int color = -1;

	while (objs != NULL)
	{
		if (objs->ft_intersect(objs, rtv1->camera->location, dir))
		{
			objs->normal = objs->ft_get_normal(objs, dir);
			if (is_first)
			{
				min_distance = ft_length(ft_dif(objs->intersect_point, rtv1->camera->location));
				nearest_obj = objs;
				is_first = 0;
				continue;				
			}
			distance = ft_length(ft_dif(objs->intersect_point, rtv1->camera->location));
			if (distance < min_distance)
			{
				min_distance = distance;
				nearest_obj = objs;
			}
		}
		objs = objs->next;
	}
	if (nearest_obj)
		return (ft_ray_to_light(rtv1, nearest_obj));
	return (2147483647);
}