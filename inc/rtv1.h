#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <math.h>
# include <pthread.h>
# include <fcntl.h>

# include "../libft/includes/libft.h"
# include "vector3d.h"

# define WIDTH 		800
# define HEIGHT 	800

# define THREADS	4

# define ABS(x)		(x) > 0 ? (x) : -(x)
# define DROUND(d)	ABS(d) < 0.001 ? 0 : (d)

typedef struct  	s_color
{
	t_vector3d		rgb;
}			   		t_color;

typedef struct  	s_camera
{
	t_vector3d 		location;
	t_vector3d 		rotation;
}			   		t_camera;

typedef enum 		t_light_type
{
					AMBIENT,
					DIFFUSE
}					e_light_type;

typedef struct  	s_light
{
	t_vector3d 		location;
	t_vector3d 		rotation;	
	float	 		intensity;
	e_light_type	type;
	struct s_light	*next;
}			   		t_light;

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
	int				(*ft_intersect)(const void *data, const t_vector3d cam_pos,
						t_vector3d direction, const t_vector3d vec_cam_to_obj);
	t_color			(*ft_get_color)(const void *data, const t_vector3d in_pnt);
	t_vector3d		(*ft_get_normal)(const void *data);
	void			(*ft_destructor)(void *data);
	struct s_object *next;
}              		t_object;

typedef	struct  	s_sphere
{
	float       	radius;
}					t_sphere;

t_object			*ft_new_sphere(t_vector3d location, t_vector3d rotation,
						float radius, t_vector3d rgb);
int 				ft_intersect_sphere(const void *data,
						const t_vector3d camera_pos,
						t_vector3d direction, const t_vector3d vec_cam_to_obj);
t_vector3d 			ft_get_normal_sphere(const void *data);

typedef	struct  	s_cylinder
{
	float       	radius;
}					t_cylinder;

t_object			*ft_new_cylinder(t_vector3d location, t_vector3d rotation,
						float radius, t_vector3d rgb);
int 				ft_intersect_cylinder(const void *data,
						const t_vector3d camera_pos,
						t_vector3d direction, const t_vector3d vec_cam_to_obj);
t_vector3d			ft_get_normal_cylinder(const void *data);

typedef	struct  	s_cone
{
	float       	angle_degree;
	float			angle_rad;
}					t_cone;

t_object			*ft_new_cone(t_vector3d location, t_vector3d rotation,
						float angle_degree, t_vector3d rgb);
int 				ft_intersect_cone(const void *data,
						const t_vector3d camera_pos,
						t_vector3d direction, const t_vector3d vec_cam_to_obj);
t_vector3d 			ft_get_normal_cone(const void *data);

typedef	struct  	s_plane
{
	t_vector3d     	ray_direction;
}					t_plane;

t_object			*ft_new_plane(t_vector3d location, t_vector3d rotation,
						t_vector3d rgb);
int 				ft_intersect_plane(const void *data,
						const t_vector3d camera_pos,
						t_vector3d direction, const t_vector3d vec_camera_to_obj);
t_vector3d 			ft_get_normal_plane(const void *data);

typedef struct  	s_rtv1
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_Surface 	*surface;
	t_object    	*objects;
	t_camera		*camera;
	t_light 		*light_sources;
	float			environment_light;
}					t_rtv1;

t_rtv1				*ft_initialize_program();
void				ft_memory_clean(t_rtv1 *rtv1);
void				ft_exit(t_rtv1 *rtv1, int is_with_error,
						char *message);

t_object   			*ft_add_obj(t_rtv1 *rtv1, t_object *new_obj);
t_light    			*ft_add_light(t_rtv1 *rtv1, t_light *new_light);

void				ft_parse(int fd, t_rtv1 *rtv1);
int					ft_parse_data(int fd, t_rtv1 *rtv1, char *title);
int					ft_parse_get_vector_param(int fd, t_vector3d *param,
						char *param_name);

void				ft_draw_loop(t_rtv1 *rtv1);
void				*ft_draw_calculation(void *data);
void				ft_drawing(t_rtv1 *rtv1);
void				ft_put_pixel_to_surface(t_rtv1 *rtv1,
						int x, int y, int color);
t_vector3d			ft_canvas_to_viewport(int x, int y);

void				ft_switch_event(t_rtv1 *rtv1);
void				ft_manage_key_input(t_rtv1 *rtv1);

int					ft_ray_tracing_proccess(t_rtv1 *rtv1, t_vector3d dir);
int					ft_color_to_int(t_color color);
float				ft_get_min_t(float a, float b, float c);
void				ft_change_objects_directions(t_object *objs);

int					ft_ray_to_light(t_rtv1 *rtv1, t_object *obj);

t_camera			*ft_new_camera(t_vector3d location, t_vector3d rotation);
t_light				*ft_new_light(t_vector3d location, t_vector3d rotation,
						float intensity, e_light_type type);
t_vector3d			ft_value_clamper(t_vector3d v, int max_value, int is_positive);

#endif
