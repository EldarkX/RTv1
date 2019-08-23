#include "../inc/rtv1.h"

int ft_intersect_sphere(const void *data, const t_vector3d camera_pos,
	t_vector3d direction)
{
	t_vector3d camera_sphere_vector;
	t_object *obj;
	t_sphere *sphere;
	double a[2];
	double discriminant;

	obj = (t_object *)data;
	sphere = (t_sphere *)obj->data;
	camera_sphere_vector = ft_dif(camera_pos, obj->location);
	a[0] = ft_dot(direction, direction);
	a[1] = 2 * ft_dot(camera_sphere_vector, direction);
	a[2] = ft_dot(camera_sphere_vector, camera_sphere_vector) - sphere->radius * sphere->radius;
	discriminant = a[1] * a[1] - 4 * a[0] * a[2];
	if (discriminant < 0)
		return (0);
	float t1, t2, min_t, max_t;

	t1 = (-a[1] + ft_sqrt(discriminant)) / (2 * a[0]);
	t2 = (-a[1] - ft_sqrt(discriminant)) / (2 * a[0]);

	if (t1 < t2)
	{
		min_t = t1;
		max_t = t2;
	}
	else
	{
		min_t = t2;
		max_t = t1;
	}
	t1 = (min_t >= 0 ? min_t : max_t);
	obj->intersect_point = ft_add(camera_pos, ft_vector_product_number(direction, min_t));
	return (t1 > 0);
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
	double discriminant;

	obj = (t_object *)data;
	cylinder = (t_cylinder *)obj->data;
	camera_cylinder_vector = ft_dif(camera_pos, obj->location);
	a[0] = direction.x * direction.x + direction.z * direction.z;
	a[1] = 2 * (camera_cylinder_vector.x * direction.x + camera_cylinder_vector.z * direction.z);
	a[2] = camera_cylinder_vector.x * camera_cylinder_vector.x + camera_cylinder_vector.z * camera_cylinder_vector.z - 
		cylinder->radius * cylinder->radius;

	discriminant = a[1] * a[1] - 4 * a[0] * a[2];
	if (discriminant < 0)
		return (0);

	float t1, t2;

	t1 = (-a[1] + ft_sqrt(discriminant)) / (2 * a[0]);
	t2 = (-a[1] - ft_sqrt(discriminant)) / (2 * a[0]);

	if (t1 > t2)
	{
		float tmp;
		tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
	t1 = camera_cylinder_vector.y + t1 * direction.y;
	t2 = camera_cylinder_vector.y + t2 * direction.y;
	if (t1 > obj->location.y && t1 < (cylinder->height + obj->location.y))
		return (1);
	else if (t2 > obj->location.y && t2 < (cylinder->height + obj->location.y))
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
	double discriminant;

	obj = (t_object *)data;
	cone = (t_cone *)obj->data;
	camera_cone_vector = ft_dif(camera_pos, obj->location);
	a[0] = direction.x * direction.x + direction.z * direction.z - direction.y * direction.y;
	a[1] = 2 * (camera_cone_vector.x * direction.x + camera_cone_vector.z * direction.z - camera_cone_vector.y * direction.y);
	a[2] = camera_cone_vector.x * camera_cone_vector.x + camera_cone_vector.z * camera_cone_vector.z - 
		camera_cone_vector.y * camera_cone_vector.y;
	
	discriminant = a[1] * a[1] - 4 * a[0] * a[2];
	if (discriminant < 0)
		return (0);

	float t1, t2;

	t1 = (-a[1] + ft_sqrt(discriminant)) / (2 * a[0]);
	t2 = (-a[1] - ft_sqrt(discriminant)) / (2 * a[0]);

	/*if (t1 > t2)
	{
		float tmp;
		tmp = t1;
		t1 = t2;
		t2 = tmp;
	}*/
	t1 = camera_cone_vector.y + t1 * direction.y;
	t2 = camera_cone_vector.y + t2 * direction.y;

	if (t1 > obj->location.y && t1 < (obj->location.y + obj->location.y))
		return (1);
	else if (t2 > obj->location.y && t2 < (obj->location.y + obj->location.y))
		return (1);
	return (0);
}