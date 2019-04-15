/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/15 12:29:45 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			redraw_img(t_env *e)
{
	const int		col = DEF_COLOR;
	const int		x = 20;
	int				y;

	mlx_clear_window(e->mlx_ptr, e->win_ptr);
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
	if (e->flags.interface_on)
	{
		y = 10;
		mlx_string_put(e->mlx_ptr, e->win_ptr, x, y, col, MSG_MOVE);
		mlx_string_put(e->mlx_ptr, e->win_ptr, x, y += 20, col, MSG_ZOOM_A);
		mlx_string_put(e->mlx_ptr, e->win_ptr, x, y += 20, col, MSG_ZOOM_Z);
		mlx_string_put(e->mlx_ptr, e->win_ptr, x, y += 20, col, MSG_INTERF);
		mlx_string_put(e->mlx_ptr, e->win_ptr, x, y += 20, col, MSG_ROTATE);
		mlx_string_put(e->mlx_ptr, e->win_ptr, x, y += 20, col, MSG_ANIMATE);
		mlx_string_put(e->mlx_ptr, e->win_ptr, x, y += 20, col, MSG_RESET);
		mlx_string_put(e->mlx_ptr, e->win_ptr, x, y += 20, col, MSG_STYLE);
		mlx_string_put(e->mlx_ptr, e->win_ptr, x, y += 20, col, MSG_EXIT);
	}
}

static int		px_to_img(int *buffer, t_line *l, t_si_pt crd, int color)
{
	crd.x += l->offset.x;
	crd.y += l->offset.y;
	if (0 <= crd.x && WIN_WIDTH > crd.x
	&& 0 <= crd.y && WIN_HEIGHT > crd.y)
		buffer[crd.y * WIN_WIDTH + crd.x] = color;
	return (1);
}

void			draw_line(int *buffer, t_line *l, int64_t x, int64_t y)
{
	l->delt = (t_si_pt){ l->end.x - x < 0 ? -1 : 1, l->end.y - y < 0 ? -1 : 1 };
	l->len = (t_si_pt){ l->end.x - x < 0 ? (l->end.x - x) * -1 : l->end.x - x,
						l->end.y - y < 0 ? (l->end.y - y) * -1 : l->end.y - y };
	l->len_max = (l->len.y > l->len.x) ? l->len.y : l->len.x;
	if (l->len_max++ == 0)
		px_to_img(buffer, l, (t_si_pt){ x, y }, l->color);
	l->d = l->len.y <= l->len.x ? -l->len.x : -l->len.y;
	while (l->len_max--)
	{
		px_to_img(buffer, l, (t_si_pt){ x, y }, l->color);
		l->d += 2 * (l->len.y <= l->len.x ? l->len.y : l->len.x);
		if (l->len.y <= l->len.x)
			x += l->delt.x;
		else
			y += l->delt.y;
		if (l->d > 0)
		{
			l->d -= 2 * (l->len.y <= l->len.x ? l->len.x : l->len.y);
			if (l->len.y <= l->len.x)
				y += l->delt.y;
			else
				x += l->delt.x;
		}
	}
}

static void		draw_map_dots(t_px **map, int *buf, t_param p)
{
	t_line	line;
	size_t	x;
	size_t	y;

	if (!map || !(*map) || !buf)
		return ;
	y = UINT64_MAX;
	while (p.rows > ++y)
	{
		x = UINT64_MAX;
		while (p.cols > ++x)
		{
			line.offset = p.move;
			px_to_img(buf, &line,
				(t_si_pt){ (int)map[y][x].pt.x * p.scale.x,
							(int)map[y][x].pt.y * p.scale.y -
							(int)map[y][x].pt.z * p.scale.z }, map[y][x].color);
		}
	}
}

void			draw_map(t_env *e, t_px **map, int *buf, t_param param)
{
	const t_flags	flags = e->flags;
	const int		connection_on = flags.con_on;

	ft_clear_img_buff(buf, WIN_WIDTH, WIN_HEIGHT);
	if (flags.ver_on)
		conn_vertical(map, buf, param, connection_on);
	if (flags.sla_on)
		conn_slash(map, buf, param, connection_on);
	if (flags.hor_on)
		conn_horizontal(map, buf, param, connection_on);
	if (flags.bsl_on)
		conn_backslash(map, buf, param, connection_on);
	if (flags.fdf_on)
		conn_fdf(map, buf, param, connection_on);
	if (flags.dot_on)
		draw_map_dots(map, buf, param);
	redraw_img(e);
}
