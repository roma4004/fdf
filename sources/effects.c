/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:44:39 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 21:15:56 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_map_vertical(t_win *win, t_line *line, t_param *p, int c)
{
	size_t	y;
	size_t	x;
	t_px	**map;

	if (!win)
		return ;
	y = -1;
	map = win->map;
	while (++y < p->rows - 1)
	{
		x = -1;
		while (++x < p->cols - 1)
		{
			line->color = map[y][x].color;
			line->end_x = (int)(map[y][x].x * p->sc_x);
			line->end_y = (int)(map[y][x].y * p->sc_y - map[y][x].z * p->sc_z);
			draw_line(win, line, (int)(map[y + 1][x].x * p->sc_x),
								(int)(map[y + 1][x].y * p->sc_y -
									map[y + c][x].z * p->sc_z));
		}
	}
	redraw_img(win);
}

void	draw_map_backslash(t_win *win, t_line *line, t_param *p, int c)
{
	size_t	y;
	size_t	x;
	t_px	**map;

	if (!win)
		return ;
	y = -1;
	map = win->map;
	while (++y < p->rows - 1)
	{
		x = -1;
		while (++x < p->cols - 1)
		{
			line->color = map[y][x].color;
			line->end_x = (int)(map[y][x].x * p->sc_x);
			line->end_y = (int)(map[y][x].y * p->sc_y - map[y][x].z * p->sc_z);
			draw_line(win, line, (int)(map[y + 1][x + 1].x * p->sc_x),
								(int)(map[y + 1][x + 1].y * p->sc_y -
									map[y + c][x + c].z * p->sc_z));
		}
	}
	redraw_img(win);
}

void	draw_map_horizontal(t_win *win, t_line *line, t_param *p, int c)
{
	size_t	y;
	size_t	x;
	t_px	**map;

	if (!win)
		return ;
	y = -1;
	map = win->map;
	while (++y < p->rows - 1)
	{
		x = -1;
		while (++x < p->cols - 1)
		{
			line->color = map[y][x].color;
			line->end_x = (int)(map[y][x].x * p->sc_x);
			line->end_y = (int)(map[y][x].y * p->sc_y - map[y][x].z * p->sc_z);
			draw_line(win, line, (int)(map[y][x + 1].x * p->sc_x),
								(int)(map[y][x + 1].y * p->sc_y -
									map[y][x + c].z * p->sc_z));
		}
	}
	redraw_img(win);
}

void	draw_map_slash(t_win *win, t_line *line, t_param *p, int c)
{
	size_t	x;
	size_t	y;
	t_px	**map;

	if (!win)
		return ;
	y = -1;
	map = win->map;
	while (++y < p->rows - 1)
	{
		x = -1;
		while (++x < p->cols - 1)
		{
			line->color = map[y][x].color;
			line->end_x = (int)(map[y][x + 1].x * p->sc_x);
			line->end_y = (int)(map[y][x + 1].y * p->sc_y
								- map[y][x + c].z * p->sc_z);
			draw_line(win, line, (int)(map[y + 1][x].x * p->sc_x),
								(int)(map[y + 1][x].y * p->sc_y -
									map[y + c][x].z * p->sc_z));
		}
	}
	redraw_img(win);
}

void	draw_map_fdf(t_win *win, t_line *line, t_param *p, int c)
{
	size_t	x;
	size_t	y;
	t_px	**map;

	if (!win)
		return ;
	y = -1;
	map = win->map;
	while (++y < p->rows && (x = -1))
		while (++x < p->cols)
		{
			line->color = map[y][x].color;
			line->end_x = (int)(map[y][x].x * p->sc_x);
			line->end_y = (int)(map[y][x].y * p->sc_y - map[y][x].z * p->sc_z);
			if (x < p->cols - 1)
				draw_line(win, line, (int)(map[y][x + 1].x * p->sc_x),
									(int)(map[y][x + 1].y * p->sc_y -
										map[y][x + c].z * p->sc_z));
			if (y < p->rows - 1)
				draw_line(win, line, (int)(map[y + 1][x].x * p->sc_x),
									(int)(map[y + 1][x].y * p->sc_y -
										map[y + c][x].z * p->sc_z));
		}
	redraw_img(win);
}
