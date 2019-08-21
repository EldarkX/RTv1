#include "../inc/rtv1.h"

int ft_color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) |
		(color.b << 0));
}



int ft_ray_tracing_proccess(t_rtv1 *rtv1, t_vector3d dir)
{
	t_vector3d intersect_point;
	t_object *objs = rtv1->objects;

	while (objs != NULL)
	{
		if (objs->ft_intersect(objs, rtv1->camera->location, dir, &intersect_point))
		{
			return (ft_ray_to_light(rtv1, objs, intersect_point));
		}
		objs = objs->next;
	}
	return (2147483647);
}