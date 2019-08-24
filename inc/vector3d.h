#ifndef VECTOR3D_H
# define VECTOR3D_H

# define DTR(d)	((double)d * (M_PI / 180))

typedef struct  s_vector3d
{
				float x;
				float y;
				float z;
}				t_vector3d;

t_vector3d		ft_new_vector(float x, float y, float z);
t_vector3d		ft_add(t_vector3d v1, t_vector3d v2);
t_vector3d		ft_dif(t_vector3d v1, t_vector3d v2);
float			ft_dot(t_vector3d v1, t_vector3d v2);
t_vector3d		ft_normalize(t_vector3d v);
float			ft_length(t_vector3d v);
t_vector3d		ft_vector_product_number(t_vector3d v, float number);
void			ft_print_vector(t_vector3d v, char *name);
t_vector3d		ft_rot_x(t_vector3d v, double a);
t_vector3d		ft_rot_y(t_vector3d v, double a);
t_vector3d		ft_rot_z(t_vector3d v, double a);
t_vector3d		ft_rot_xyz(t_vector3d v, t_vector3d r);

#endif