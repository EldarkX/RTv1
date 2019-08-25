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
	/*t_vector3d 	point_to_light;
	float 		obj_intensity;
	float 		x;

	/*point_to_light = ft_dif(rtv1->light_sources->location, obj->intersect_point);
	x = ft_dot(point_to_light, obj->normal);*/
	t_color new = obj->color;
	/*if (x <= 0)
	{
		new.r = 255 * rtv1->environment_light;
		new.g = 255 * rtv1->environment_light;
		new.b = 255 * rtv1->environment_light;
	}
	else
	{
		obj_intensity = rtv1->environment_light + rtv1->light_source->intensity *
			x / ft_length(point_to_light);
		new.r = (float)new.r * obj_intensity;
		new.g = (float)new.g * obj_intensity;
		new.b = (float)new.b * obj_intensity;
	}*/
	return (ft_color_to_int(new));
}