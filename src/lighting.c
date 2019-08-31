#include "../inc/rtv1.h"

int 	ft_color_to_int(t_color color)
{
	return
		(
			((unsigned int)color.rgb.x << 16) | 
			((unsigned int)color.rgb.y << 8) |
			((unsigned int)color.rgb.z << 0)
		);
}

int		ft_ray_to_light(t_rtv1 *rtv1, t_object *obj)
{
	t_vector3d 	point_to_light;
	float 		obj_intensity;
	float 		x;

	point_to_light = ft_dif(rtv1->light_sources->location, obj->intersect_point);
	x = ft_dot(point_to_light, obj->normal);
	t_color new = obj->color;
	if (x <= 0)
	{
		new.rgb.x = 255 * 0.1;
		new.rgb.y = 255 * 0.1;
		new.rgb.z = 255 * 0.1;
	}
	else
	{
		obj_intensity = 0.1 + 0.9 * x / ft_length(point_to_light);
		new.rgb.x = (float)new.rgb.x * obj_intensity;
		new.rgb.y = (float)new.rgb.y * obj_intensity;
		new.rgb.z = (float)new.rgb.z * obj_intensity;
	}
	return (ft_color_to_int(new));
}