#include "../inc/rtv1.h"

int ft_intersect_sphere(const void *data, const t_vector3d camera_pos,
			t_vector3d direction, const t_vector3d vec_camera_to_obj)
{
	t_object *obj;
	t_sphere *sphere;
	double a[3];

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
	t_object	*obj;
	t_plane		*plane;
	double		dot_dirs;

	obj = (t_object *)data;
	plane = (t_plane *)obj->data;
	dot_dirs = ft_dot(direction, obj->direction);
	if (dot_dirs == 0)
		return (0);
	else
		obj->t = -ft_dot(vec_camera_to_obj, obj->direction) / dot_dirs;
	if (obj->t <= 1)
		return (0);
	plane->ray_direction = direction;
	obj->intersect_point = ft_add(camera_pos, ft_vector_product_number(direction, obj->t));
	return (1);
}

int 	ft_intersect_cylinder(const void *data, const t_vector3d camera_pos,
			t_vector3d direction, const t_vector3d vec_camera_to_obj)
{
	t_object *obj;
	t_cylinder *cylinder;
	double a[3];
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
	t_object *obj;
	t_cone *cone;
	double a[3];
	float dot_dirs;
	float dot_cam_dirs;

	obj = (t_object *)data;
	cone = (t_cone *)obj->data;
	dot_dirs = ft_dot(direction, obj->direction);
	dot_cam_dirs = ft_dot(vec_camera_to_obj, obj->direction);
	a[0] = ft_dot(direction, direction) - (1 + cone->angle_rad *
		cone->angle_rad) * dot_dirs * dot_dirs;
	a[1] = 2 * ft_dot(direction, vec_camera_to_obj) - (1 + cone->angle_rad *
		cone->angle_rad) * dot_dirs * dot_cam_dirs;
	a[2] = ft_dot(vec_camera_to_obj, vec_camera_to_obj) -
		(1 + cone->angle_rad * cone->angle_rad) * dot_cam_dirs * dot_cam_dirs;
	
	obj->t = ft_get_min_t(a[0], a[1], a[2]);
	if (obj->t == -1)
		return (0);
	obj->intersect_point = ft_add(camera_pos, ft_vector_product_number(direction, obj->t));
	return (1);
}