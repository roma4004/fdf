/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/18 18:06:29 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "main.h"

static void		zoom_offset(t_env *win, int zoom_offset,
							int only_z, t_param *param)
{
	int64_t		x;
	int64_t		y;
	int64_t		z;

	x = param->scale.x;
	y = param->scale.y;
	z = param->scale.z;
	if (only_z == 0)
		param->scale =
				(t_si_3pt){ x + (x + zoom_offset >= 0 ? zoom_offset : 0),
							y + (y + zoom_offset >= 0 ? zoom_offset : 0),
							z + (z + zoom_offset >= 0 ? zoom_offset : 0) };
	else
		param->scale.z += zoom_offset;
	draw_map(win);
}

static void		animate(t_env *win)
{
	ft_clear_img_buff(win->buffer, WIN_WIDTH, WIN_HEIGHT);
	if (++win->param.frame_cnt == 4)
		win->param.frame_cnt = 0;
	if (win->param.frame_cnt == 0)
		draw_map_vertical(win, win->buffer, &win->param, win->flags.con_on);
	if (win->param.frame_cnt == 1)
		draw_map_slash(win, win->buffer, &win->param, win->flags.con_on);
	if (win->param.frame_cnt == 2)
		draw_map_horizontal(win, win->buffer, &win->param, win->flags.con_on);
	if (win->param.frame_cnt == 3)
		draw_map_backslash(win, win->buffer, &win->param, win->flags.con_on);
}

static void		deal_keyboard2(int key, t_env *win)
{
	char	ch;

	if (((key == NUM_1 || key == ONE) && ft_toggle(&win->flags.ver_on))
	|| ((key == NUM_2 || key == TWO) && ft_toggle(&win->flags.sla_on))
	|| ((key == NUM_3 || key == THREE) && ft_toggle(&win->flags.hor_on))
	|| ((key == NUM_4 || key == FOUR) && ft_toggle(&win->flags.bsl_on))
	|| ((key == NUM_5 || key == FIVE) && ft_toggle(&win->flags.fdf_on))
	|| ((key == NUM_6 || key == SIX) && ft_toggle(&win->flags.con_on))
	|| ((key == NUM_7 || key == SEVEN) && ft_toggle(&win->flags.dot_on))
	|| ((key == NUM_8 || key == EIGHT) && ft_toggle(&win->flags.interface_on)))
		draw_map(win);
	else if (key == ESC)
		exit_x(win);
	else if ((key == Q && (ch = 'y'))
		|| (key == W && (ch = 'x'))
		|| (key == E && (ch = 'z')))
		rotate_map(win, ch, 2);
	else if ((key == A && (ch = 'y'))
		|| (key == S && (ch = 'x'))
		|| (key == D && (ch = 'z')))
		rotate_map(win, ch, -2);
	else if (key == ENTER)
		animate(win);
	else if (key == R)
		reset(win);
}

int				deal_keyboard(int key, t_env *win)
{
	t_si_pt		pt;
	int			sign;

	if (!win)
		return (1);
	pt = (t_si_pt){ 0, 0 };
	if ((key == ARROW_LEFT && (pt.x = -10))
	|| (key == ARROW_UP && (pt.y = -10))
	|| (key == ARROW_DOWN && (pt.y = 10))
	|| (key == ARROW_RIGHT && (pt.x = 10)))
	{
		win->param.offset = (t_si_pt){ win->param.offset.x + pt.x,
										win->param.offset.y + pt.y };
		draw_map(win);
	}
	else if (((key == NUM_MINUS || key == NINE) && (sign = -1))
		|| ((key == NUM_PLUS || key == ZERO) && (sign = 1)))
		zoom_offset(win, sign, 1, &win->param);
	else if (((key == MINUS) && (sign = -1))
		|| ((key == PLUS) && (sign = 1)))
		zoom_offset(win, sign, 0, &win->param);
	else
		deal_keyboard2(key, win);
	return (0);
}

int				deal_mouse(int key, int x, int y, t_env *win)
{
	if (!win)
		return (1);
	y++;
	x++;
	if (key == MOUSE_SCROLL_UP)
		zoom_offset(win, -1, 0, &win->param);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom_offset(win, 1, 0, &win->param);
	return (0);
}
