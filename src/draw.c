/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/30 15:37:21 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	px_put(t_win *win, int x, int y, int color)
{
	mlx_pixel_put(win->mlx_ptr, win->win_ptr,
		x + win->param->offset_x,
		y + win->param->offset_y, color);
}

void		draw_line(t_win *win, t_line *l, int x, int y)
{
	l->dx = (l->end_x - x >= 0 ? 1 : -1);
	l->dy = (l->end_y - y >= 0 ? 1 : -1);
	l->len_x = ((l->end_x - x) < 0) ? (l->end_x - x) * -1 : l->end_x - x;
	l->len_y = ((l->end_y - y) < 0) ? (l->end_y - y) * -1 : l->end_y - y;
	l->len = (l->len_y > l->len_x) ? l->len_y : l->len_x;
	if (l->len++ == 0)
		px_put(win, x, y, l->color);
	l->d = ((l->len_y <= l->len_x) ? -l->len_x : -l->len_y);
	while (l->len--)
	{
		px_put(win, x, y, l->color);
		l->d += 2 * ((l->len_y <= l->len_x) ? l->len_y : l->len_x);
		if (l->len_y <= l->len_x)
			x += l->dx;
		else
			y += l->dy;
		if (l->d > 0)
		{
			l->d -= 2 * ((l->len_y <= l->len_x) ? l->len_x : l->len_y);
			if (l->len_y <= l->len_x)
				y += l->dy;
			else
				x += l->dx;
		}
	}
}

void		draw_map(t_win *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	if (win->flags->ver_on)
		draw_map_vertical(win, win->flags->con_on);
	if (win->flags->sla_on)
		draw_map_slash(win, win->flags->con_on);
	if (win->flags->hor_on)
		draw_map_horizontal(win, win->flags->con_on);
	if (win->flags->bsl_on)
		draw_map_backslash(win, win->flags->con_on);
	if (win->flags->fdf_on)
		draw_map_fdf(win, win->flags->con_on);
	if (win->flags->dot_on)
		draw_map_dots(win);
	if (win->flags->interface_on)
		show_interface(win);
}

void		draw_map_dots(t_win *win)
{
	size_t	x;
	size_t	y;

	if (!win || !(y = -1))
		return ;
	while (++y < win->param->rows && (x = -1))
		while (++x < win->param->cols)
			px_put(win, win->map[y][x].x * win->param->sc_x,
					win->map[y][x].y * win->param->sc_y -
					win->map[y][x].z * win->param->sc_z,
					win->map[y][x].color);
}
