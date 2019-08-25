#include"../inc/rtv1.h"
#include <stdio.h>

t_object    *ft_add_obj(t_rtv1 *rtv1, t_object *new_obj)
{
    t_object *head;

    head = rtv1->objects;
    if (head == NULL)
        return (new_obj);
    
    while (rtv1->objects->next != NULL)
        rtv1->objects = rtv1->objects->next;
    rtv1->objects->next = new_obj;
    return (head);
}

t_object    *ft_add_light_source(t_rtv1 *rtv1, t_light *new_light)
{
    t_light *head;

    head = rtv1->light_sources;
    if (head == NULL)
        return (new_light);
    
    while (rtv1->light_sources->next != NULL)
        rtv1->light_sources = rtv1->light_sources->next;
    rtv1->light_sources->next = new_light;
    return (head);
}

void ft_print_objects(t_object *start)
{
    t_object *tmp = start;

    while (tmp)
    {
        printf("1 check color = %f %f %f \n", tmp->color.rgb.x, tmp->color.rgb.y, tmp->color.rgb.z);
        printf("2 check location = %f %f %f \n", tmp->location.x, tmp->location.y, tmp->location.z);
        tmp = tmp->next;
    }
}

int main(int argc, char **argv)
{
    t_rtv1  *rtv1;
    int     fd;

    if (argc != 2)
        return (-1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (-1);
    rtv1 = ft_initialize_program();
    rtv1->objects = NULL;
    rtv1->light_sources = NULL;
    ft_parse(rtv1); 
/* temporary*/
    /*t_color color;
    color.rgb = 100;
    color.g = 70;
    color.b = 70;
    rtv1->objects = ft_add_obj(rtv1, ft_new_cone(ft_new_vector(0, 0, 5), ft_new_vector(0, 0, 0), 30, color));
    color.r = 200;
    color.g = 100;
    color.b = 200;
    rtv1->objects = ft_add_obj(rtv1, ft_new_cylinder(ft_new_vector(-8, 0, 1), ft_new_vector(0, 0, 0), 1, color)); 
    color.r = 200;
    color.g = 100;
    color.b = 200;
    rtv1->objects = ft_add_obj(rtv1, ft_new_cylinder(ft_new_vector(8, 0, 1), ft_new_vector(0, 0, 0), 1, color)); 
    color.r = 150;
    color.g = 150;
    color.b = 0;
    rtv1->objects = ft_add_obj(rtv1, ft_new_plane(ft_new_vector(0, -3, 0), ft_new_vector(0, 0, 0), color));
    color.r = 255;
    color.g = 30;
    color.b = 150;
    rtv1->objects = ft_add_obj(rtv1, ft_new_plane(ft_new_vector(0, 7, 0), ft_new_vector(0, 0, 0), color));
    color.r = 0;
    color.g = 70;
    color.b = 70;
    rtv1->objects = ft_add_obj(rtv1, ft_new_plane(ft_new_vector(0, -1, 8), ft_new_vector(90, 0, 0), color));
    color.r = 255;
    color.g = 0;
    color.b = 0;
    rtv1->objects = ft_add_obj(rtv1, ft_new_sphere(ft_new_vector(0, -1, -2), ft_new_vector(0, 0, 0), 2, color));
    color.r = 0;
    color.g = 255;
    color.b = 0;
    rtv1->objects = ft_add_obj(rtv1, ft_new_sphere(ft_new_vector(-3, -1, 0), ft_new_vector(0, 0, 0), 2, color));
    color.r = 0;
    color.g = 0;
    color.b = 255;
    rtv1->objects = ft_add_obj(rtv1, ft_new_sphere(ft_new_vector(3, -1, 0), ft_new_vector(0, 0, 0), 2, color));*/
    rtv1->camera = (t_camera *)malloc(sizeof(t_camera));
    rtv1->camera->location = ft_new_vector(0, 0, -20);
    rtv1->light_sources = (t_light *)malloc(sizeof(t_light));
    rtv1->light_sources->location = ft_new_vector(0, 3, -5);
    rtv1->light_sources->intensity = 0.9;
    ft_draw_loop(rtv1);
    ft_memory_clean(rtv1);
    return (0);
}

t_rtv1    *ft_initialize_program()
{
    t_rtv1 *rtv1;

    rtv1 = (t_rtv1 *)malloc(sizeof(t_rtv1));
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        rtv1->window = SDL_CreateWindow("RTV1 aantropo",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH,
            HEIGHT,
            0);
        if(!rtv1->window)
            ft_exit(rtv1, 1, "Could not create window.\n");
        rtv1->renderer = SDL_CreateRenderer(rtv1->window, -1, SDL_RENDERER_SOFTWARE);
        if(!rtv1->renderer)
            ft_exit(rtv1, 1, "Could not create renderer.\n");
        rtv1->surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
        if (!rtv1->surface)
            ft_exit(rtv1, 1, "Could not create surface.\n");
    }
    else
        ft_exit(rtv1, 1, "Could not init SDL.\n");
    return (rtv1);
}

void    ft_exit(t_rtv1 *rtv1, int is_with_error, char *message)
{
    if (is_with_error)
        printf("Error: %s", message);
    ft_memory_clean(rtv1);           
    exit(1); 
}

void    ft_memory_clean(t_rtv1 *rtv1)
{
    SDL_DestroyWindow(rtv1->window);
    if (rtv1)
        free(rtv1);
    SDL_Quit();
}
