#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <math.h>
# include <pthread.h>

# include "vector3d.h"

# define WIDTH 600
# define HEIGHT 600

# define THREADS 4

/* temporary */

double ft_sqrt(double number);

/***/

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
	float	 	intensiy;
}			   	t_light;

typedef struct 		s_object
{
	void 			*data;
	t_color    		color;	
	t_vector3d 		location;
	t_vector3d 		rotation;
	t_vector3d 		scale;
	int				(*ft_intersect)(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, t_vector3d *intersect_point);
	t_color			(*ft_get_color)(const void *data, const t_vector3d intersect_point);
	t_vector3d		(*ft_get_normal)(const void *data, const t_vector3d intersect_point);
	void			(*ft_destructor)(void *data);
	struct s_object *next;
}              		t_object;

typedef	struct  	s_sphere
{
	float       	radius;
}					t_sphere;

t_object			*ft_new_sphere(t_vector3d location,float radius,
						t_color color);
int 				ft_intersect_sphere(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, t_vector3d *intersect_point);

typedef	struct  	s_cylinder
{
	float       	radius;
	float			height;
}					t_cylinder;

t_object			*ft_new_cylinder(t_vector3d location,float radius, float height,
						t_color color);
int 				ft_intersect_cylinder(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, t_vector3d *intersect_point);

typedef	struct  	s_cone
{
	float       	radius;
	float			height;
}					t_cone;

t_object			*ft_new_cone(t_vector3d location,float radius, float height,
						t_color color);
int 				ft_intersect_cone(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, t_vector3d *intersect_point);

typedef	struct  	s_plane
{
	t_vector3d     	n;
}					t_plane;

t_object			*ft_new_plane(t_vector3d location, t_color color);
int 				ft_intersect_plane(const void *data, const t_vector3d camera_pos,
						t_vector3d direction, t_vector3d *intersect_point);

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

int				ft_ray_to_light(t_rtv1 *rtv1, t_object *obj,
					t_vector3d intersect_point);

#endif
