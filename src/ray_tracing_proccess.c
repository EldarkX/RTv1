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
	float	min_distance;

	while (objs != NULL)
	{
		if (objs->ft_intersect(objs, rtv1->camera->location,
			dir, ft_dif(rtv1->camera->location, objs->location)))
		{
			if (!nearest_obj)
				nearest_obj = objs;	
			else if (objs->t < min_distance)
				nearest_obj = objs;
			min_distance = nearest_obj->t;
		}
		objs = objs->next;
	}
	if (nearest_obj)
	{
		nearest_obj->normal_dir = ft_dot(dir, nearest_obj->direction) *
			nearest_obj->t + ft_dot(ft_dif(rtv1->camera->location,
			nearest_obj->location),	nearest_obj->direction);
		nearest_obj->normal = nearest_obj->ft_get_normal(nearest_obj, dir);
	}
	return (nearest_obj ? ft_ray_to_light(rtv1, nearest_obj) : 2147483647);
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
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
	if ((t1 <= t2 && t1 > 1) || (t1 > 1 && t2 <= 1))
		return (t1);
	if ((t2 <= t2 && t2 > 1) || (t2 > 1 && t1 <= 1))
		return (t2);
	return (-1);
}

void	ft_change_objects_directions(t_object *objs)
{
	t_object *obj;

	obj = objs;
	while (obj)
	{
		obj->direction = ft_rot_xyz(obj->direction, obj->rotation);
		obj = obj->next;
	}
}