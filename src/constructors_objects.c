#include "../inc/rtv1.h"

t_vector3d	ft_value_clamper(t_vector3d v, int max_value)
{
	t_vector3d result_v;

	result_v.x = (int)v.x % max_value;
	result_v.y = (int)v.y % max_value;
	result_v.z = (int)v.z % max_value;
	return(result_v);
}

t_object	*ft_new_sphere(t_vector3d location, t_vector3d rotation, float radius, t_color color)
{
	t_sphere *new_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	t_object *obj = (t_object *)malloc(sizeof(t_object));
	
	new_sphere->radius = radius <= 0 ? 1 : (int)radius % 100;

	obj->data = new_sphere;
	obj->location = location;
	obj->rotation = ft_value_clamper(rotation, 360);
	obj->direction = ft_new_vector(0, 1, 0);
	obj->color.rgb = ft_value_clamper(rotation, 255);
	obj->ft_intersect = ft_intersect_sphere;
	obj->ft_get_normal = ft_get_normal_sphere;
	obj->next = NULL;
	return (obj);
}

t_object	*ft_new_cylinder(t_vector3d location, t_vector3d rotation, float radius, t_color color)
{
	t_cylinder *new_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder)); 
	t_object *obj = (t_object *)malloc(sizeof(t_object));

	new_cylinder->radius = radius <= 0 ? 1 : (int)radius % 100;

	obj->data = new_cylinder;
	obj->location = location;
	obj->rotation = ft_value_clamper(rotation, 360);
	obj->direction = ft_new_vector(0, 1, 0);
	obj->color.rgb = ft_value_clamper(rotation, 255);
	obj->ft_intersect = ft_intersect_cylinder;
	obj->ft_get_normal = ft_get_normal_cylinder;
	obj->next = NULL;
	return (obj);
}

t_object	*ft_new_cone(t_vector3d location, t_vector3d rotation, float angle_degree, t_color color)
{
	t_cone *new_cone = (t_cone *)malloc(sizeof(t_cone)); 
	t_object *obj = (t_object *)malloc(sizeof(t_object));

	new_cone->angle_degree = angle_degree == 0 ? 1 : (int)angle_degree % 150;
	new_cone->angle_rad = DTR(angle_degree);

	obj->data = new_cone;
	obj->location = location;
	obj->rotation = ft_value_clamper(rotation, 360);
	obj->direction = ft_new_vector(0, 1, 0);
	obj->color.rgb = ft_value_clamper(rotation, 255);
	obj->ft_intersect = ft_intersect_cone;
	obj->ft_get_normal = ft_get_normal_cone;
	obj->next = NULL;
	return (obj);
}

t_object	*ft_new_plane(t_vector3d location, t_vector3d rotation, t_color color)
{
	t_plane *new_plane = (t_plane *)malloc(sizeof(t_plane)); 
	t_object *obj = (t_object *)malloc(sizeof(t_object));

	obj->data = new_plane;
	obj->location = location;
	obj->rotation = ft_value_clamper(rotation, 360);
	obj->direction = ft_new_vector(0, 1, 0);
	obj->color.rgb = ft_value_clamper(rotation, 255);
	obj->ft_intersect = ft_intersect_plane;
	obj->ft_get_normal = ft_get_normal_plane;
	obj->next = NULL;
	return (obj);
}