#include "../inc/rtv1.h"

t_vector3d	ft_value_clamper(t_vector3d v, int max_value)
{
	t_vector3d result_v;

	result_v.x = (int)v.x % max_value;
	result_v.y = (int)v.y % max_value;
	result_v.z = (int)v.z % max_value;
	return(result_v);
}

t_camera	*ft_camera_constructor(t_vector3d location, t_vector3d rotation)
{
	t_camera *new_camera;

	new_camera = (t_camera *)malloc(sizeof(t_camera));
	new_camera->location = location;
	new_camera->rotation = ft_value_clamper(rotation, 360);
	return (new_camera);
}