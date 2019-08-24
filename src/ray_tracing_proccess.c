#include "../inc/rtv1.h"

int 	ft_color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) |
		(color.b << 0));
}

int 	ft_ray_tracing_proccess(t_rtv1 *rtv1, t_vector3d dir)
{
	t_object *objs = rtv1->objects;
	t_object *nearest_obj = NULL;
	int color = -1;
	float	min_distance;
	int is_first = 1;

	while (objs != NULL)
	{
		if (objs->ft_intersect(objs, rtv1->camera->location, dir))
		{
			objs->normal = objs->ft_get_normal(objs, dir);
			if (is_first)
			{
				min_distance = objs->t;
				nearest_obj = objs;
				is_first = 0;
				continue;				
			}
			if (objs->t < min_distance)
			{
				min_distance = objs->t;;
				nearest_obj = objs;
			}
		}
		objs = objs->next;
	}
	if (nearest_obj)
		return (ft_ray_to_light(rtv1, nearest_obj));
	return (2147483647);
}

float	ft_get_min_t(float a, float b, float c)
{
	double 	discriminant;
	float	t1;
	float	t2;

	discriminant = b * b - 4 * a * c;
	discriminant = DROUND(discriminant);
	if (discriminant < 0)
		return (-1);

	t1 = (-b + ft_sqrt(discriminant)) / (2 * a);
	t2 = (-b - ft_sqrt(discriminant)) / (2 * a);

	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	if ((t2 <= t1 && t2 >= 0) || (t2 >= 0 && t1 < 0))
		return (t2);
	return (-1);
}