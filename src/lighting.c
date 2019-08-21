#include "../inc/rtv1.h"

int		ft_ray_to_light(t_rtv1 *rtv1, t_object *obj, t_vector3d intersect_point)
{
	t_vector3d normal;
	t_vector3d point_to_light = ft_dif(rtv1->light_source->location, intersect_point);

	normal = ft_dif(intersect_point, obj->location);
	normal.x /= ft_length(normal);
	normal.y /= ft_length(normal);
	normal.z /= ft_length(normal);

	float obj_intensity;

	obj_intensity = rtv1->environment_light + ft_dot(point_to_light, normal) /
		((ft_length(normal) * ft_length(point_to_light)));
	t_color new = obj->color;
	new.r *= obj_intensity;
	new.g *= obj_intensity;
	new.b *= obj_intensity;

	return (ft_color_to_int(new));
}