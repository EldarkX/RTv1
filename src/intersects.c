#include "../inc/rtv1.h"

int ft_intersect_sphere(const void *data, const t_vector3d camera_pos,
			t_vector3d direction, const t_vector3d vec_camera_to_obj)
{
	t_object *obj;
	t_sphere *sphere;
	double a[2];

	obj = (t_object *)data;
	sphere = (t_sphere *)obj->data;
	a[0] = ft_dot(direction, direction);
	a[1] = 2 * ft_dot(vec_camera_to_obj, direction);
	a[2] = ft_dot(vec_camera_to_obj, vec_camera_to_obj) - sphere->radius * sphere->radius;
	obj->t = ft_get_min_t(a[0], a[1], a[2]);
	if (obj->t == -1)
		return (0);
	obj->intersect_point = ft_add(camera_pos, ft_vector_product_number(direction, obj->t));
	return (1);
}

int 	ft_intersect_plane(const void *data, const t_vector3d camera_pos,
			t_vector3d direction, const t_vector3d vec_camera_to_obj)
{
	t_object *obj;
	t_plane  *plane;
	t_vector3d camera_plane_vector;
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
			t_vector3d direction, const t_vector3d vec_camera_to_obj)
{
	t_object *obj;
	t_cylinder *cylinder;
	double a[2];
	float dot_dirs;
	float dot_cam_dirs;

	obj = (t_object *)data;
	cylinder = (t_cylinder *)obj->data;
	if (ft_length(vec_camera_to_obj) <= cylinder->radius)
		return (0);
	dot_dirs = ft_dot(direction, obj->direction);
	dot_cam_dirs = ft_dot(vec_camera_to_obj, obj->direction);
	a[0] = ft_dot(direction, direction) - dot_dirs * dot_dirs;
	a[1] = 2 * ft_dot(direction, vec_camera_to_obj) - dot_dirs * dot_cam_dirs;
	a[2] = ft_dot(vec_camera_to_obj, vec_camera_to_obj) -
			dot_cam_dirs * dot_cam_dirs -  cylinder->radius * cylinder->radius;
	obj->t = ft_get_min_t(a[0], a[1], a[2]);
	if (obj->t == -1)
		return (0);
	obj->intersect_point = ft_add(camera_pos, ft_vector_product_number(direction, obj->t));
	return (1);
}

int 	ft_intersect_cone(const void *data, const t_vector3d camera_pos,
			t_vector3d direction, const t_vector3d vec_camera_to_obj)
{
	t_vector3d camera_cone_vector;
	t_object *obj;
	t_cone *cone;
	double a[2];

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
	return (1);
}