#include "../inc/rtv1.h"

t_object	*ft_new_sphere(t_vector3d location, t_vector3d rotation,
	float radius, t_vector3d rgb)
{
	t_sphere *new_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	t_object *obj = (t_object *)malloc(sizeof(t_object));
	
	new_sphere->radius = radius;

	obj->data = new_sphere;
	obj->location = location;
	obj->rotation = ft_value_clamper(rotation, 360, 0);
	obj->direction = ft_new_vector(0, 1, 0);
	obj->color.rgb = ft_value_clamper(rgb, 255, 1);
	obj->ft_intersect = ft_intersect_sphere;
	obj->ft_get_normal = ft_get_normal_sphere;
	obj->next = NULL;
	return (obj);
}

t_object	*ft_new_cylinder(t_vector3d location, t_vector3d rotation,
	float radius, t_vector3d rgb)
{
	t_cylinder *new_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder)); 
	t_object *obj = (t_object *)malloc(sizeof(t_object));

	new_cylinder->radius = radius;

	obj->data = new_cylinder;
	obj->location = location;
	obj->rotation = ft_value_clamper(rotation, 360, 0);
	obj->direction = ft_new_vector(0, 1, 0);
	obj->color.rgb = ft_value_clamper(rgb, 255, 1);
	obj->ft_intersect = ft_intersect_cylinder;
	obj->ft_get_normal = ft_get_normal_cylinder;
	obj->next = NULL;
	return (obj);
}

t_object	*ft_new_cone(t_vector3d location, t_vector3d rotation,
	float angle_degree, t_vector3d rgb)
{
	t_cone *new_cone = (t_cone *)malloc(sizeof(t_cone)); 
	t_object *obj = (t_object *)malloc(sizeof(t_object));

	new_cone->angle_degree = angle_degree;
	new_cone->angle_rad = DTR(angle_degree);

	obj->data = new_cone;
	obj->location = location;
	obj->rotation = ft_value_clamper(rotation, 360, 0);
	obj->direction = ft_new_vector(0, 1, 0);
	obj->color.rgb = ft_value_clamper(rgb, 255, 1);
	obj->ft_intersect = ft_intersect_cone;
	obj->ft_get_normal = ft_get_normal_cone;
	obj->next = NULL;
	return (obj);
}

t_object	*ft_new_plane(t_vector3d location, t_vector3d rotation,
	t_vector3d rgb)
{
	t_plane *new_plane = (t_plane *)malloc(sizeof(t_plane)); 
	t_object *obj = (t_object *)malloc(sizeof(t_object));

	obj->data = new_plane;
	obj->location = location;
	obj->rotation = ft_value_clamper(rotation, 360, 0);
	obj->direction = ft_new_vector(0, 1, 0);
	obj->color.rgb = ft_value_clamper(rgb, 255, 1);
	obj->ft_intersect = ft_intersect_plane;
	obj->ft_get_normal = ft_get_normal_plane;
	obj->next = NULL;
	return (obj);
}