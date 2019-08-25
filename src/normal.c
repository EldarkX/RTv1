#include "../inc/rtv1.h"

t_vector3d ft_get_normal_sphere(const void *data)
{
	t_vector3d normal;
	t_object *obj;

	obj = (t_object *)data;
	normal = ft_dif(obj->intersect_point, obj->location);
	normal = ft_normalize(normal);
	return (normal);
}

/*TMP*/
t_vector3d ft_get_normal_cylinder(const void *data)
{
	t_vector3d normal;
	t_object *obj;

	obj = (t_object *)data;
	normal = ft_dif(ft_dif(obj->intersect_point, obj->location),
		ft_vector_product_number(obj->direction,
			obj->normal_dir));
	normal = ft_normalize(normal);
	return (normal);
}

/*TMP*/
t_vector3d ft_get_normal_cone(const void *data)
{
	t_vector3d normal;
	t_object *obj;
	t_cone	*cone;

	obj = (t_object *)data;
	cone = (t_cone *)obj->data;
	normal = ft_dif(ft_dif(obj->intersect_point, obj->location),
		ft_vector_product_number(obj->direction,
			obj->normal_dir * (1 + cone->angle_rad * cone->angle_rad)));
	normal = ft_normalize(normal);
	return (normal);
}

t_vector3d ft_get_normal_plane(const void *data)
{	
	t_object	*obj;
	t_plane		*plane;

	obj = (t_object *)data;
	plane = (t_plane *)obj->data;
	if (ft_dot(plane->ray_direction, obj->direction) <= 0)
		return (ft_normalize(obj->direction));
	return (ft_normalize(ft_vector_product_number(obj->direction, -1)));
}