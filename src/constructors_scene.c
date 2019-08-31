#include "../inc/rtv1.h"

t_vector3d	ft_value_clamper(t_vector3d v, int max_value, int is_positive)
{
	t_vector3d result_v;

	if ((int)v.x % max_value != 0 && (int)v.x != 0)
		result_v.x = (int)v.x % max_value;
	else
		result_v.x = (int)v.x;
	if ((int)v.y % max_value != 0 && (int)v.y != 0)
		result_v.y = (int)v.y % max_value;
	else
		result_v.y = (int)v.y;
	if ((int)v.z % max_value != 0 && (int)v.z != 0)		
		result_v.z = (int)v.z % max_value;
	else
		result_v.z = (int)v.z;
	result_v.x = is_positive ? ABS((int)result_v.x) : result_v.x;
	result_v.y = is_positive ? ABS((int)result_v.y) : result_v.y;
	result_v.z = is_positive ? ABS((int)result_v.z) : result_v.z;
	return(result_v);
}

t_camera	*ft_new_camera(t_vector3d location, t_vector3d rotation)
{
	t_camera *new_camera;

	new_camera = (t_camera *)malloc(sizeof(t_camera));
	new_camera->location = location;
	new_camera->rotation = ft_value_clamper(rotation, 360, 0);
	return (new_camera);
}

t_light	*ft_new_light(t_vector3d location, t_vector3d rotation,
	float intensity, e_light_type type)
{
	t_light *new_light;

	new_light = (t_light *)malloc(sizeof(t_light));
	new_light->location = location;
	new_light->rotation = ft_value_clamper(rotation, 360, 0);
	new_light->intensity = intensity >= 0 ? 0.1 : intensity;
	new_light->type = type;
	return (new_light);
}