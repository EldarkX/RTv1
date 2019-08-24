#include "../inc/rtv1.h"

void	ft_draw_loop(t_rtv1 *rtv1)
{
	pthread_t threads[THREADS];
	int i;

	i = -1;
	ft_change_objects_directions(rtv1->objects);
	while (++i < THREADS)
		pthread_create(&threads[i], NULL, ft_draw_calculation, (void *)rtv1);
	while (1)
	{
		if (SDL_PollEvent(&rtv1->event))
			ft_switch_event(rtv1);
		else
		{
			i = -1;
			while (++i < THREADS)
				pthread_join(threads[i], NULL);
			ft_draw_calculation(rtv1);
			ft_drawing(rtv1);
		}
	}
}

void	*ft_draw_calculation(void *data)
{
	static int thread_number = 0;
	int start_x;
	int end_x;
	t_vector3d dir;

	t_rtv1 *rtv1 = (t_rtv1 *)data;
	if (thread_number == THREADS)
		thread_number = 0;
	start_x = 0 + thread_number * (WIDTH / THREADS);
	end_x = start_x + (WIDTH / THREADS);

	int x, y = -1;
	while (++y < HEIGHT)
	{
		x = start_x - 1;
		while (++x < end_x)
		{
			dir = ft_normalize(ft_canvas_to_viewport(x, y));
			ft_put_pixel_to_surface(rtv1, x, y, ft_ray_tracing_proccess(rtv1, dir));
		}
	}
	thread_number++;
	return (0);
}

void	ft_drawing(t_rtv1 *rtv1)
{
	SDL_Rect	src;
	SDL_Rect	dst;
	SDL_Texture	*texture;

	texture = SDL_CreateTextureFromSurface(rtv1->renderer, rtv1->surface);
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	src.x = 0;
	src.y = 0;
	dst.x = src.x;
	dst.y = src.y;
	dst.w = src.w;
	dst.h = src.h;
	SDL_RenderClear(rtv1->renderer);
	SDL_RenderCopy(rtv1->renderer, texture, &src, &dst);
	SDL_RenderPresent(rtv1->renderer);
	SDL_DestroyTexture(texture);
}

void	ft_put_pixel_to_surface(t_rtv1 *rtv1, int x, int y, int color)
{
	int index;

	SDL_LockSurface(rtv1->surface);
	index = rtv1->surface->pitch * y +
		x * rtv1->surface->format->BytesPerPixel;
	*(unsigned *)(rtv1->surface->pixels + index) = color;
	SDL_UnlockSurface(rtv1->surface);
}

t_vector3d	ft_canvas_to_viewport(int x, int y)
{
	t_vector3d dir;

	dir.x = (float)x / WIDTH - 0.5;
	dir.y = 0.5 + (float)-y / HEIGHT;
	dir.z = 1;
	return (dir);
}