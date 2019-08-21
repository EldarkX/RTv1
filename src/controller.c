#include "../inc/rtv1.h"

void	ft_switch_event(t_rtv1 *rtv1)
{
	if (rtv1->event.type == SDL_QUIT)
		ft_exit(rtv1, 0, NULL);
	else if (rtv1->event.type == SDL_KEYUP)
		ft_manage_key_input(rtv1);
}

void	ft_manage_key_input(t_rtv1 *rtv1)
{
	int key;

	key = rtv1->event.key.keysym.sym;
	if (key == SDLK_ESCAPE)
		ft_exit(rtv1, 0, NULL);
}