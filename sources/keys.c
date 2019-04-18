/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/18 13:46:40 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "main.h"

static void		zoom(t_env *e, int offset, int only_z, t_si_3pt *scale)
{
	if (!scale)
		return ;
	if (only_z)
		scale->z += offset;
	else
		*scale = (t_si_3pt){ scale->x + (scale->x + offset >= 0 ? offset : 0),
							scale->y + (scale->y + offset >= 0 ? offset : 0),
							scale->z + (scale->z + offset >= 0 ? offset : 0) };
	draw_map(e, e->map, e->buffer, e->param);
}

static void		animate(t_env *e, t_px **map, int *buffer)
{
	const int			connection_on = e->flags.con_on;
	const t_param		param = e->param;
	int					frame_cnt;

	if (!e || !map || !(*map) || !buffer)
		return ;
	frame_cnt = e->param.frame_cnt;
	ft_clear_img_buff(buffer, WIN_WIDTH, WIN_HEIGHT);
	if (4 == ++frame_cnt)
		frame_cnt = 0;
	if (0 == frame_cnt)
		conn_vertical(map, buffer, param, connection_on);
	if (1 == frame_cnt)
		conn_slash(map, buffer, param, connection_on);
	if (2 == frame_cnt)
		conn_horizontal(map, buffer, param, connection_on);
	if (3 == frame_cnt)
		conn_backslash(map, buffer, param, connection_on);
	e->param.frame_cnt = frame_cnt;
	redraw_img(e);
}

static void		deal_keyboard2(int key, t_env *e)
{
	char	ch;

	if (((NUM_1 == key || ONE == key) && ft_toggle(&e->flags.ver_on))
	|| ((NUM_2 == key || TWO == key) && ft_toggle(&e->flags.sla_on))
	|| ((NUM_3 == key || THREE == key) && ft_toggle(&e->flags.hor_on))
	|| ((NUM_4 == key || FOUR == key) && ft_toggle(&e->flags.bsl_on))
	|| ((NUM_5 == key || FIVE == key) && ft_toggle(&e->flags.fdf_on))
	|| ((NUM_6 == key || SIX == key) && ft_toggle(&e->flags.con_on))
	|| ((NUM_7 == key || SEVEN == key) && ft_toggle(&e->flags.dot_on))
	|| ((NUM_8 == key || EIGHT == key) && ft_toggle(&e->flags.interface_on)))
		draw_map(e, e->map, e->buffer, e->param);
	else if (ESC == key)
		exit_x(e);
	else if ((Q == key && (ch = 'y'))
		|| (W == key && (ch = 'x'))
		|| (E == key && (ch = 'z')))
		rotate_map(e, e->map, ch, 2.0);
	else if ((A == key && (ch = 'y'))
		|| (S == key && (ch = 'x'))
		|| (D == key && (ch = 'z')))
		rotate_map(e, e->map, ch, -2.0);
	else if (ENTER == key)
		animate(e, e->map, e->buffer);
	else if (R == key)
		reset(e, e->map, e->buffer, e->param);
}

int				deal_keyboard(int key, t_env *e)
{
	int		zoom_offset;
	int		y;
	int		x;

	if (!e)
		return (1);
	y = 0;
	x = 0;
	if ((ARROW_LEFT == key && (x = -10))
	|| (ARROW_UP == key && (y = -10))
	|| (ARROW_DOWN == key && (y = 10))
	|| (ARROW_RIGHT == key && (x = 10)))
	{
		e->param.move = (t_si_2pt){ e->param.move.x + x, e->param.move.y + y };
		draw_map(e, e->map, e->buffer, e->param);
	}
	else if (((NUM_MINUS == key || NINE == key) && (zoom_offset = -1))
		|| ((NUM_PLUS == key || ZERO == key) && (zoom_offset = 1)))
		zoom(e, zoom_offset, 1, &e->param.scale);
	else if ((MINUS == key && (zoom_offset = -1))
		|| (PLUS == key && (zoom_offset = 1)))
		zoom(e, zoom_offset, 0, &e->param.scale);
	else
		deal_keyboard2(key, e);
	return (0);
}

int				deal_mouse(int key, int x, int y, t_env *e)
{
	if (!e)
		return (1);
	(void)y;
	(void)x;
	if (MOUSE_SCROLL_UP == key)
		zoom(e, -1, 0, &e->param.scale);
	else if (MOUSE_SCROLL_DOWN == key)
		zoom(e, 1, 0, &e->param.scale);
	return (0);
}
