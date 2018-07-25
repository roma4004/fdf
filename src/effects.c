/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:44:39 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/21 20:44:42 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_map_vertical(t_win *win, int c)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < win->param->rows - 1 && (x = -1))
		while (++x < win->param->cols - 1)
		{
			line->color = win->map[y][x].color;
			line->end_x = win->map[y][x].x * win->param->sc_x;
			line->end_y = win->map[y][x].y * win->param->sc_y
						- win->map[y][x].z * win->param->sc_z;
			draw_line(win, line,
				win->map[y + 1][x].x * win->param->sc_x,
				win->map[y + 1][x].y * win->param->sc_y -
				win->map[y + c][x].z * win->param->sc_z);
		}
}

void	draw_map_backslash(t_win *win, int c)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < win->param->rows - 1 && (x = -1))
		while (++x < win->param->cols - 1)
		{
			line->color = win->map[y][x].color;
			line->end_x = win->map[y][x].x * win->param->sc_x;
			line->end_y = win->map[y][x].y * win->param->sc_y
						- win->map[y][x].z * win->param->sc_z;
			draw_line(win, line,
				win->map[y + 1][x + 1].x * win->param->sc_x,
				win->map[y + 1][x + 1].y * win->param->sc_y -
				win->map[y + c][x + c].z * win->param->sc_z);
		}
}

void	draw_map_horizontal(t_win *win, int c)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < win->param->rows - 1 && (x = -1))
		while (++x < win->param->cols - 1)
		{
			line->color = win->map[y][x].color;
			line->end_x = win->map[y][x].x * win->param->sc_x;
			line->end_y = win->map[y][x].y * win->param->sc_y
						- win->map[y][x].z * win->param->sc_z;
			draw_line(win, line,
				win->map[y][x + 1].x * win->param->sc_x,
				win->map[y][x + 1].y * win->param->sc_y -
				win->map[y][x + c].z * win->param->sc_z);
		}
}

void	draw_map_slash(t_win *win, int c)
{
	t_line	*line;
	size_t	x;
	size_t	y;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < win->param->rows - 1 && (x = -1))
		while (++x < win->param->cols - 1)
		{
			line->color = win->map[y][x].color;
			line->end_x = win->map[y][x + 1].x * win->param->sc_x;
			line->end_y = win->map[y][x + 1].y * win->param->sc_y
						- win->map[y][x + c].z * win->param->sc_z;
			draw_line(win, line,
				win->map[y + 1][x].x * win->param->sc_x,
				win->map[y + 1][x].y * win->param->sc_y -
				win->map[y + c][x].z * win->param->sc_z);
		}
}

void	draw_map_fdf(t_win *win, int c)
{
	t_line	*line;
	size_t	x;
	size_t	y;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < win->param->rows && (x = -1))
		while (++x < win->param->cols)
		{
			line->color = win->map[y][x].color;
			line->end_x = win->map[y][x].x * win->param->sc_x;
			line->end_y = win->map[y][x].y * win->param->sc_y
						- win->map[y][x].z * win->param->sc_z;
			if (x < win->param->cols - 1)
				draw_line(win, line,
					win->map[y][x + 1].x * win->param->sc_x,
					win->map[y][x + 1].y * win->param->sc_y -
					win->map[y][x + c].z * win->param->sc_z);
			if (y < win->param->rows - 1)
				draw_line(win, line,
					win->map[y + 1][x].x * win->param->sc_x,
					win->map[y + 1][x].y * win->param->sc_y -
					win->map[y + c][x].z * win->param->sc_z);
		}
}
