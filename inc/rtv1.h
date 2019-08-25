#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <math.h>
# include <pthread.h>

# include "vector3d.h"

# define WIDTH 		800
# define HEIGHT 	800

# define THREADS	4

# define ABS(x)		(x) > 0 ? (x) : -(x)
# define DROUND(d)	ABS(d) < 0.001 ? 0 : (d)

typedef struct  s_color
{
	int			r;
	int			g;
	int			b;
	int			alpha;
}			   	t_color;

typedef struct  s_camera
{
	t_vector3d 	location;
	t_vector3d 	rotation;
}			   	t_camera;

typedef struct  s_light
{
	t_vector3d 	location;
	float	 	intensity;
}			   	t_light;

typedef struct 		s_object
{
	void 			*data;
	t_color    		color;	
	t_vector3d 		location;
	t_vector3d 		rotation;
	t_vector3d 		direction;
	t_vector3d		normal;
	t_vector3d		intersect_point;
	float			normal_dir;
	float 			t;
	int				(*ft_intersect)(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, const t_vector3d vec_camera_to_obj);
	t_color			(*ft_get_color)(const void *data, const t_vector3d intersect_point);
	t_vector3d		(*ft_get_normal)(const void *data, t_vector3d dir);
	void			(*ft_destructor)(void *data);
	struct s_object *next;
}              		t_object;

typedef	struct  	s_sphere
{
	float       	radius;
}					t_sphere;

t_object			*ft_new_sphere(t_vector3d location, t_vector3d rotation, float radius,
						t_color color);
int 				ft_intersect_sphere(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, const t_vector3d vec_camera_to_obj);
t_vector3d 			ft_get_normal_sphere(const void *data, t_vector3d dir);

typedef	struct  	s_cylinder
{
	float       	radius;
}					t_cylinder;

t_object			*ft_new_cylinder(t_vector3d location, t_vector3d rotation, float radius, t_color color);
int 				ft_intersect_cylinder(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, const t_vector3d vec_camera_to_obj);
t_vector3d			ft_get_normal_cylinder(const void *data, t_vector3d dir);

typedef	struct  	s_cone
{
	float       	angle_degree;
	float			angle_rad;
}					t_cone;

t_object			*ft_new_cone(t_vector3d location, t_vector3d rotation, float angle_degree, t_color color);
int 				ft_intersect_cone(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, const t_vector3d vec_camera_to_obj);
t_vector3d 			ft_get_normal_cone(const void *data, t_vector3d dir);

typedef	struct  	s_plane
{
	t_vector3d     	n;
}					t_plane;

t_object			*ft_new_plane(t_vector3d location, t_vector3d rotation, t_color color);
int 				ft_intersect_plane(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, const t_vector3d vec_camera_to_obj);
t_vector3d 			ft_get_normal_plane(const void *data, t_vector3d dir);

typedef struct  	s_rtv1
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_Surface 	*surface;
	t_object    	*objects;
	t_camera		*camera;
	t_light 		*light_source;
	float			environment_light;
}					t_rtv1;

void			ft_initialize_program(t_rtv1 *rtv1);
void			ft_memory_clean(t_rtv1 *rtv1);
void			ft_exit(t_rtv1 *rtv1, int is_with_error,
					char *message);

void			ft_draw_loop(t_rtv1 *rtv1);
void			*ft_draw_calculation(void *data);
void			ft_drawing(t_rtv1 *rtv1);
void			ft_put_pixel_to_surface(t_rtv1 *rtv1,
					int x, int y, int color);
t_vector3d		ft_canvas_to_viewport(int x, int y);

void			ft_switch_event(t_rtv1 *rtv1);
void			ft_manage_key_input(t_rtv1 *rtv1);

int 			ft_ray_tracing_proccess(t_rtv1 *rtv1, t_vector3d dir);
int 			ft_color_to_int(t_color color);
float			ft_get_min_t(float a, float b, float c);
void			ft_change_objects_directions(t_object *objs);

int				ft_ray_to_light(t_rtv1 *rtv1, t_object *obj);

#endif
