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

t_light    *ft_add_light(t_rtv1 *rtv1, t_light *new_light)
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
        ft_print_vector(tmp->location, "location");
        ft_print_vector(tmp->rotation, "rotation");
        ft_print_vector(tmp->color.rgb, "color");
        tmp = tmp->next;
    }
}

void ft_print_lights(t_light *start)
{
    t_light *tmp = start;

    while (tmp)
    {
        ft_print_vector(tmp->location, "location");
        ft_print_vector(tmp->rotation, "rotation");
        tmp = tmp->next;
    }
}

void ft_print_camera(t_camera *camera)
{
    if (camera)
    {
        ft_print_vector(camera->location, "location");
        ft_print_vector(camera->rotation, "rotation");
    }
}

/*TO DO : CHECK ON VALUES IN PARSER BEFORE USING" */

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
    rtv1->camera = NULL;
    ft_parse(fd, rtv1);
    if (close(fd) == -1)
        ft_exit(rtv1, 1, "Can`t close file.");
    if (rtv1->camera == NULL)
        ft_exit(rtv1, 1, "There isn't a camera.");
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
            ft_exit(rtv1, 1, "Could not create window.");
        rtv1->renderer = SDL_CreateRenderer(rtv1->window, -1, SDL_RENDERER_SOFTWARE);
        if(!rtv1->renderer)
            ft_exit(rtv1, 1, "Could not create renderer.");
        rtv1->surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
        if (!rtv1->surface)
            ft_exit(rtv1, 1, "Could not create surface.");
    }
    else
        ft_exit(rtv1, 1, "Could not init SDL.");
    return (rtv1);
}

void    ft_exit(t_rtv1 *rtv1, int is_with_error, char *message)
{
    if (is_with_error)
        printf("Error: %s\n", message);
    ft_memory_clean(rtv1);           
    exit(1); 
}

void    ft_memory_clean(t_rtv1 *rtv1)
{
    t_object    *objs;
    t_light     *lights;
    void        *tmp;

    if (rtv1)
    {
        SDL_DestroyWindow(rtv1->window);
        objs = rtv1->objects;
        while (objs)
        {
            tmp = objs;
            objs = objs->next;
            free(tmp);
        }
        lights = rtv1->light_sources;
        while (lights)
        {
            tmp = lights;
            lights = lights->next;
            free(tmp);
        }
        if (rtv1->camera)
            free(rtv1->camera);
        free(rtv1);
    }
    SDL_Quit();
}
