/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/18 16:51:48 by dromanic         ###   ########.fr       */
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
	if (crd.x >= 0 && crd.x < WIN_WIDTH && crd.y >= 0 && crd.y < WIN_HEIGHT)
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

static void		draw_map_dots(t_env *win)
{
	t_line	line;
	size_t	x;
	size_t	y;
	t_si_pt	pt;

	if (!win)
		return ;
	y = UINT64_MAX;
	while (++y < win->param.rows)
	{
		x = UINT64_MAX;
		while (++x < win->param.cols)
		{
			pt = (t_si_pt){ (int)win->map[y][x].x * win->param.scale.x,
							(int)win->map[y][x].y * win->param.scale.y -
							(int)win->map[y][x].z * win->param.scale.z };
			line.offset = win->param.offset;
			px_to_img(win->buffer, &line, pt, win->map[y][x].color);
		}
	}
	redraw_img(win);
}

void			draw_map(t_env *win)
{
	ft_clear_img_buff(win->buffer, WIN_WIDTH, WIN_HEIGHT);
	if (win->flags.ver_on)
		draw_map_vertical(win, win->buffer, &win->param, win->flags.con_on);
	if (win->flags.sla_on)
		draw_map_slash(win, win->buffer, &win->param, win->flags.con_on);
	if (win->flags.hor_on)
		draw_map_horizontal(win, win->buffer, &win->param, win->flags.con_on);
	if (win->flags.bsl_on)
		draw_map_backslash(win, win->buffer, &win->param, win->flags.con_on);
	if (win->flags.fdf_on)
		draw_map_fdf(win, win->buffer, &win->param, win->flags.con_on);
	if (win->flags.dot_on)
		draw_map_dots(win);
	redraw_img(win);
}
