/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/14 22:17:19 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			redraw_img(t_env *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	if (win->flags.interface_on)
		show_interface(win);
}

static int		px_to_img(int *buffer, t_line *l, t_si_pt crd, int color)
{
	crd.x += l->offset.x;
	crd.y += l->offset.y;
	if (crd.x >= 0 && crd.x < WIN_WIDTH
	&& crd.y >= 0 && crd.y < WIN_HEIGHT)
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
	while (++y < p.rows)
	{
		x = UINT64_MAX;
		while (++x < p.cols)
		{
			line.offset = p.offset;
			px_to_img(buf, &line,
				(t_si_pt){ (int)map[y][x].pt.x * p.scale.x,
							(int)map[y][x].pt.y * p.scale.y -
							(int)map[y][x].pt.z * p.scale.z }, map[y][x].color);
		}
	}
}

void			draw_map(t_env *win, t_px **map, int *buf, t_param param)
{
	ft_clear_img_buff(buf, WIN_WIDTH, WIN_HEIGHT);
	if (win->flags.ver_on)
		conn_vertical(map, buf, param, win->flags.con_on);
	if (win->flags.sla_on)
		conn_slash(map, buf, param, win->flags.con_on);
	if (win->flags.hor_on)
		conn_horizontal(map, buf, param, win->flags.con_on);
	if (win->flags.bsl_on)
		conn_backslash(map, buf, param, win->flags.con_on);
	if (win->flags.fdf_on)
		conn_fdf(map, buf, param, win->flags.con_on);
	if (win->flags.dot_on)
		draw_map_dots(map, buf, param);
	redraw_img(win);
}
