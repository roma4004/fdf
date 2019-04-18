/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/18 13:34:37 by dromanic         ###   ########.fr       */
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

static int		px_to_img(int *buffer, t_line *l, t_si_2pt crd, int color)
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
	l->delta = (t_si_2pt){ 0 > l->end.x - x ? -1 : 1,
							0 > l->end.y - y ? -1 : 1 };
	l->len = (t_si_2pt){ 0 > l->end.x - x ? (l->end.x - x) * -1 : l->end.x - x,
						0 > l->end.y - y ? (l->end.y - y) * -1 : l->end.y - y };
	l->len_max = (l->len.y > l->len.x) ? l->len.y : l->len.x;
	if (0 == l->len_max++)
		px_to_img(buffer, l, (t_si_2pt){ x, y }, l->color);
	l->d = l->len.y <= l->len.x ? -l->len.x : -l->len.y;
	while (l->len_max--)
	{
		px_to_img(buffer, l, (t_si_2pt){ x, y }, l->color);
		l->d += 2 * (l->len.y <= l->len.x ? l->len.y : l->len.x);
		if (l->len.y <= l->len.x)
			x += l->delta.x;
		else
			y += l->delta.y;
		if (0 < l->d)
		{
			l->d -= 2 * (l->len.y <= l->len.x ? l->len.x : l->len.y);
			if (l->len.y <= l->len.x)
				y += l->delta.y;
			else
				x += l->delta.x;
		}
	}
}

static void		draw_map_dots(t_px **map, int *buf, t_param p)
{
	t_line		line;
	size_t		x;
	size_t		y;

	y = UINT64_MAX;
	while (p.rows > ++y)
	{
		x = UINT64_MAX;
		while (p.cols > ++x)
		{
			line.offset = p.move;
			px_to_img(buf,
						&line,
						(t_si_2pt){ (int)map[y][x].pt.x * p.scale.x,
									(int)map[y][x].pt.y * p.scale.y -
									(int)map[y][x].pt.z * p.scale.z },
						map[y][x].color);
		}
	}
}

void			draw_map(t_env *e, t_px **map, int *buffer, t_param param)
{
	const t_flags		flags = e->flags;
	const int			connection_on = flags.con_on;

	if (!map || !(*map) || !buffer)
		return ;
	ft_clear_img_buff(buffer, WIN_WIDTH, WIN_HEIGHT);
	if (flags.ver_on)
		conn_vertical(map, buffer, param, connection_on);
	if (flags.sla_on)
		conn_slash(map, buffer, param, connection_on);
	if (flags.hor_on)
		conn_horizontal(map, buffer, param, connection_on);
	if (flags.bsl_on)
		conn_backslash(map, buffer, param, connection_on);
	if (flags.fdf_on)
		conn_fdf(map, buffer, param, connection_on);
	if (flags.dot_on)
		draw_map_dots(map, buffer, param);
	redraw_img(e);
}
