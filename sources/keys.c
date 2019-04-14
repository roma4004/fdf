/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/14 22:19:33 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "main.h"

static void		zoom(t_env *win, int offset, int only_z, t_si_3pt *scale)
{
	if (only_z)
		scale->z += offset;
	else
		*scale = (t_si_3pt){ scale->x + (scale->x + offset >= 0 ? offset : 0),
							scale->y + (scale->y + offset >= 0 ? offset : 0),
							scale->z + (scale->z + offset >= 0 ? offset : 0) };
	draw_map(win, win->map, win->buffer, win->param);
}

static void		animate(t_env *win)
{
	ft_clear_img_buff(win->buffer, WIN_WIDTH, WIN_HEIGHT);
	if (++win->param.frame_cnt == 4)
		win->param.frame_cnt = 0;
	if (0 == win->param.frame_cnt)
		conn_vertical(win->map, win->buffer, win->param, win->flags.con_on);
	if (1 == win->param.frame_cnt)
		conn_slash(win->map, win->buffer, win->param, win->flags.con_on);
	if (2 == win->param.frame_cnt)
		conn_horizontal(win->map, win->buffer, win->param, win->flags.con_on);
	if (3 == win->param.frame_cnt)
		conn_backslash(win->map, win->buffer, win->param, win->flags.con_on);
	redraw_img(win);
}

static void		deal_keyboard2(int key, t_env *win)
{
	char	ch;

	if (((NUM_1 == key || ONE == key) && ft_toggle(&win->flags.ver_on))
	|| ((NUM_2 == key || TWO == key) && ft_toggle(&win->flags.sla_on))
	|| ((NUM_3 == key || THREE == key) && ft_toggle(&win->flags.hor_on))
	|| ((NUM_4 == key || FOUR == key) && ft_toggle(&win->flags.bsl_on))
	|| ((NUM_5 == key || FIVE == key) && ft_toggle(&win->flags.fdf_on))
	|| ((NUM_6 == key || SIX == key) && ft_toggle(&win->flags.con_on))
	|| ((NUM_7 == key || SEVEN == key) && ft_toggle(&win->flags.dot_on))
	|| ((NUM_8 == key || EIGHT == key) && ft_toggle(&win->flags.interface_on)))
		draw_map(win, win->map, win->buffer, win->param);
	else if (ESC == key)
		exit_x(win);
	else if ((Q == key && (ch = 'y'))
		|| (W == key && (ch = 'x'))
		|| (E == key && (ch = 'z')))
		rotate_map(win, ch, 2);
	else if ((A == key && (ch = 'y'))
		|| (S == key && (ch = 'x'))
		|| (D == key && (ch = 'z')))
		rotate_map(win, ch, -2);
	else if (ENTER == key)
		animate(win);
	else if (R == key)
		reset(win);
}

int				deal_keyboard(int key, t_env *win)
{
	t_si_pt		pt;
	int			zoom_offset;

	if (!win)
		return (1);
	pt = (t_si_pt){ 0, 0 };
	if ((ARROW_LEFT == key && (pt.x = -10))
	|| (ARROW_UP == key && (pt.y = -10))
	|| (ARROW_DOWN == key && (pt.y = 10))
	|| (ARROW_RIGHT == key && (pt.x = 10)))
	{
		win->param.offset = (t_si_pt){ win->param.offset.x + pt.x,
										win->param.offset.y + pt.y };
		draw_map(win, win->map, win->buffer, win->param);
	}
	else if (((NUM_MINUS == key || NINE == key) && (zoom_offset = -1))
		|| ((NUM_PLUS == key || ZERO == key) && (zoom_offset = 1)))
		zoom(win, zoom_offset, 1, &win->param.scale);
	else if (((MINUS == key) && (zoom_offset = -1))
		|| ((PLUS == key) && (zoom_offset = 1)))
		zoom(win, zoom_offset, 0, &win->param.scale);
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
		zoom(win, -1, 0, &win->param.scale);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom(win, 1, 0, &win->param.scale);
	return (0);
}
