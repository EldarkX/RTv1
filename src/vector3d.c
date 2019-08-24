#include "../inc/rtv1.h"

t_vector3d ft_new_vector(float x, float y, float z)
{
	t_vector3d vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector3d ft_add(t_vector3d v1, t_vector3d v2)
{
	t_vector3d v;

	v.x = v2.x + v1.x;
	v.y = v2.y + v1.y;
	v.z = v2.z + v1.z;
	return (v);
}

t_vector3d ft_dif(t_vector3d v1, t_vector3d v2)
{
	t_vector3d v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

float ft_dot(t_vector3d v1, t_vector3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float ft_length(t_vector3d v)
{
	return (sqrt(ft_dot(v, v)));
}

t_vector3d ft_normalize(t_vector3d v)
{
	t_vector3d	v_normal;
	float		len;

	len = ft_length(v);
	if (len == 0)
		return (v);
	v_normal.x = v.x / len;
	v_normal.y = v.y / len;
	v_normal.z = v.z / len;

	return (v_normal);
}

t_vector3d		ft_vector_product_number(t_vector3d v, float number)
{
	t_vector3d	v_res;

	v_res.x = v.x * number;
	v_res.y = v.y * number;
	v_res.z = v.z * number;
	return (v_res);
}

void			ft_print_vector(t_vector3d v, char *name)
{
	printf("%s(%f,%f,%f)\n", name, v.x, v.y, v.z);
}

t_vector3d		ft_rot_xyz(t_vector3d v, t_vector3d r)
{
	v = ft_rot_x(v, DTR(r.x));
	v = ft_rot_y(v, DTR(r.y));
	v = ft_rot_z(v, DTR(r.z));
	return (v);
}

t_vector3d	ft_rot_x(t_vector3d v, double a)
{
	t_vector3d	r;

	r.x = v.x;
	r.y = v.y * cos(a) - v.z * sin(a);
	r.z = v.y * sin(a) + v.z * cos(a);
	return (r);
}

t_vector3d	ft_rot_y(t_vector3d v, double a)
{
	t_vector3d	r;

	r.x = v.x * cos(a) + v.z * sin(a);
	r.y = v.y;
	r.z = v.z * cos(a) - v.x * sin(a);
	return (r);
}

t_vector3d	ft_rot_z(t_vector3d v, double a)
{
	t_vector3d	r;

	r.x = v.x * cos(a) - v.y * sin(a);
	r.y = v.x * sin(a) + v.y * cos(a);
	r.z = v.z;
	return (r);
}