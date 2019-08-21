#include "../inc/rtv1.h"

t_object	*ft_new_sphere(t_vector3d location, float radius, t_color color)
{
	t_sphere *new_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	t_object *obj = (t_object *)malloc(sizeof(t_object));
	
	new_sphere->radius = radius;

	obj->data = new_sphere;
	obj->location = location;
	obj->color = color;
	obj->ft_intersect = ft_intersect_sphere;
	obj->next = NULL;
	return (obj);
}

t_object	*ft_new_cylinder(t_vector3d location, float radius, float height, t_color color)
{
	t_cylinder *new_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder)); 
	t_object *obj = (t_object *)malloc(sizeof(t_object));

	new_cylinder->radius = radius;
	new_cylinder->height = height;

	obj->data = new_cylinder;
	obj->location = location;
	obj->color = color;
	obj->ft_intersect = ft_intersect_cylinder;
	obj->next = NULL;
	return (obj);
}

t_object	*ft_new_cone(t_vector3d location, float radius, float height, t_color color)
{
	t_cone *new_cone = (t_cone *)malloc(sizeof(t_cone)); 
	t_object *obj = (t_object *)malloc(sizeof(t_object));

	new_cone->radius = radius;
	new_cone->height = height;

	obj->data = new_cone;
	obj->location = location;
	obj->color = color;
	obj->ft_intersect = ft_intersect_cone;
	obj->next = NULL;
	return (obj);
}

t_object	*ft_new_plane(t_vector3d location, t_color color)
{
	t_plane *new_plane = (t_plane *)malloc(sizeof(t_plane)); 
	t_object *obj = (t_object *)malloc(sizeof(t_object));

	new_plane->n = ft_normalize(location);

	obj->data = new_plane;
	obj->location = location;
	obj->color = color;
	obj->ft_intersect = ft_intersect_plane;
	obj->next = NULL;
	return (obj);
}