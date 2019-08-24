#include "../inc/rtv1.h"

int ft_intersect_sphere(const void *data, const t_vector3d camera_pos,
	t_vector3d direction)
{
	t_vector3d camera_sphere_vector;
	t_object *obj;
	t_sphere *sphere;
	double a[2];

	obj = (t_object *)data;
	sphere = (t_sphere *)obj->data;
	camera_sphere_vector = ft_dif(camera_pos, obj->location);
	a[0] = ft_dot(direction, direction);
	a[1] = 2 * ft_dot(camera_sphere_vector, direction);
	a[2] = ft_dot(camera_sphere_vector, camera_sphere_vector) - sphere->radius * sphere->radius;
	obj->t = ft_get_min_t(a[0], a[1], a[2]);
	if (obj->t == -1)
		return (0);
	obj->intersect_point = ft_add(camera_pos, ft_vector_product_number(direction, obj->t));
	return (1);
}

int 	ft_intersect_plane(const void *data, const t_vector3d camera_pos,
			t_vector3d direction)
{
	t_object *obj;
	t_plane  *plane;
	t_vector3d camera_plane_vector;
	t_vector3d camera_n;
	float denom, result;

	obj = (t_object *)data;
	plane = (t_plane *)obj->data;
	direction = ft_normalize(direction);

	denom = ft_dot(plane->n, direction);
	if (denom > 0.000001)
	{
		camera_plane_vector = ft_dif(obj->location, camera_pos);
		result = ft_dot(camera_plane_vector, plane->n) / denom;
		obj->t = result;
		obj->intersect_point = ft_add(camera_pos, ft_vector_product_number(direction, result));
		return (result >= 0);
	}
	return (0);
}

int 	ft_intersect_cylinder(const void *data, const t_vector3d camera_pos,
			t_vector3d direction)
{
	t_vector3d camera_cylinder_vector;
	t_object *obj;
	t_cylinder *cylinder;
	double a[2];
	float t;

	obj = (t_object *)data;
	cylinder = (t_cylinder *)obj->data;
	camera_cylinder_vector = ft_dif(camera_pos, obj->location);
	a[0] = direction.x * direction.x + direction.z * direction.z;
	a[1] = 2 * (camera_cylinder_vector.x * direction.x + camera_cylinder_vector.z * direction.z);
	a[2] = camera_cylinder_vector.x * camera_cylinder_vector.x + camera_cylinder_vector.z * camera_cylinder_vector.z - 
		cylinder->radius * cylinder->radius;
	obj->t = ft_get_min_t(a[0], a[1], a[2]);
	if (obj->t == -1)
		return (0);
	t = camera_cylinder_vector.y + obj->t * direction.y;
	obj->intersect_point = ft_add(camera_pos, ft_vector_product_number(direction, obj->t));
	if (cylinder->height <= 1)
		return (1);
	if (t > obj->location.y && t < (cylinder->height + obj->location.y))
		return (1);
	return (0);
}

int 	ft_intersect_cone(const void *data, const t_vector3d camera_pos,
			t_vector3d direction)
{
	t_vector3d camera_cone_vector;
	t_object *obj;
	t_cone *cone;
	double a[2];
	float t;

	obj = (t_object *)data;
	cone = (t_cone *)obj->data;
	camera_cone_vector = ft_dif(camera_pos, obj->location);
	a[0] = direction.x * direction.x + direction.z * direction.z - direction.y * direction.y;
	a[1] = 2 * (camera_cone_vector.x * direction.x + camera_cone_vector.z * direction.z - camera_cone_vector.y * direction.y);
	a[2] = camera_cone_vector.x * camera_cone_vector.x + camera_cone_vector.z * camera_cone_vector.z - 
		camera_cone_vector.y * camera_cone_vector.y;
	
	obj->t = ft_get_min_t(a[0], a[1], a[2]);
	if (obj->t == -1)
		return (0);
	obj->intersect_point = ft_add(camera_pos, ft_vector_product_number(direction, obj->t));
	/*if (obj->intersect_point.y > obj->location.y && obj->intersect_point.y < (cone->height + obj->location.y))
		return (1);*/
	return (1);
}