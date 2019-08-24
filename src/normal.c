#include "../inc/rtv1.h"

t_vector3d ft_get_normal_sphere(const void *data, t_vector3d dir)
{
	t_vector3d normal;
	t_object *obj;

	obj = (t_object *)data;
	normal = ft_dif(obj->intersect_point, obj->location);
	normal = ft_normalize(normal);
	return (normal);
}

/*TMP*/
t_vector3d ft_get_normal_cylinder(const void *data, t_vector3d dir)
{
	t_vector3d normal;
	t_object *obj;

	obj = (t_object *)data;
	normal = ft_dif(obj->intersect_point, obj->location);
	normal = ft_normalize(ft_rot_xyz(normal, obj->rotation));
	if (ft_dot(normal, dir) < 0)
		return (normal);
	return (ft_vector_product_number(normal, -1));
}

/*TMP*/
t_vector3d ft_get_normal_cone(const void *data, t_vector3d dir)
{
	t_vector3d normal;
	t_object *obj;

	obj = (t_object *)data;
	normal = ft_dif(obj->intersect_point, obj->location);
	normal = ft_normalize(normal);
	//if (ft_dot(normal, dir) < 0)
		return (normal);
	//return (ft_vector_product_number(normal, -1));
}

t_vector3d ft_get_normal_plane(const void *data, t_vector3d dir)
{	
	t_object *obj;

	obj = (t_object *)data;
	t_vector3d plane_n = ((t_plane *)obj->data)->n;
	if (ft_dot(plane_n, dir) < 0)
		return (plane_n);
	return (ft_vector_product_number(plane_n, -1));
}