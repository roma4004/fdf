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

void	draw_map_vertical(t_win *win, int offset_y, int offset_x, int con)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	init_line(line);
	while (++y < win->map_rows - 1 && (x = -1))
		while (++x < win->map_cols - 1)
		{
			line->y1 = win->map[y + 1][x].y * win->sc_y
			    	- win->map[y + con][x].z * win->sc_z + offset_y;
			line->x1 = win->map[y + 1][x].x * win->sc_x + offset_x;
			line->y2 = win->map[y][x].y * win->sc_y
					- win->map[y][x].z * win->sc_z;
			line->x2 = win->map[y][x].x * win->sc_x;
			line->end_y = line->y2 + offset_y;
			line->end_x = line->x2 + offset_x;
			draw_line(win, line, line->y1, line->x1, win->map[y][x].color);
		}	
}

void	draw_map_backslash(t_win *win, int offset_y, int offset_x, int con)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows - 1 && (x = -1))
		while (++x < win->map_cols - 1)
		{
			line->y1 = win->map[y + 1][x + 1].y * win->sc_y
					- win->map[y + con][x + con].z * win->sc_z + offset_y;
			line->x1 = win->map[y + 1][x + 1].x * win->sc_x + offset_x;
			line->y2 = win->map[y][x].y * win->sc_y
					- win->map[y][x].z * win->sc_z;
			line->x2 = win->map[y][x].x * win->sc_x;
			line->end_y = line->y2 + offset_y;
			line->end_x = line->x2 + offset_x;
			draw_line(win, line, line->y1, line->x1, win->map[y][x].color);
		}
}

void	draw_map_horizontal(t_win *win, int offset_y, int offset_x, int con)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows - 1 && (x = -1))
		while (++x < win->map_cols - 1)
		{
			line->y1 = win->map[y][x + 1].y * win->sc_y
					- win->map[y][x + con].z * win->sc_z + offset_y;
			line->x1 = win->map[y][x + 1].x * win->sc_x + offset_x;
			line->y2 = win->map[y][x].y * win->sc_y
					- win->map[y][x].z * win->sc_z;
			line->x2 = win->map[y][x].x * win->sc_x;
			line->end_y = line->y2 + offset_y;
			line->end_x = line->x2 + offset_x;
			draw_line(win, line,  line->y1, line->x1, win->map[y][x].color);
		}
}

void	draw_map_slash(t_win *win, int offset_y, int offset_x, int con)
{
	t_line	*line;
	size_t	y;
	size_t	x;
	
	if (!win || !(line = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows - 1 && (x = -1))
		while (++x < win->map_cols - 1)
		{
			line->y1 = win->map[y + 1][x].y * win->sc_y
					- win->map[y + con][x].z * win->sc_z + offset_y;
			line->x1 = win->map[y + 1][x].x * win->sc_x + offset_x;
			line->y2 = win->map[y][x + 1].y * win->sc_y
					- win->map[y][x + con].z * win->sc_z;
			line->x2 = win->map[y][x + 1].x * win->sc_x;
			line->end_y = line->y2 + offset_y;
			line->end_x = line->x2 + offset_x;
			draw_line(win, line,  line->y1, line->x1, win->map[y][x].color);
		}
}

void	draw_map_fdf(t_win *win, int offset_y, int offset_x, int con)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows && (x = -1))
		while (++x < win->map_cols)
		{
			line->y1 = win->map[y][x + 1].y * win->sc_y
					- win->map[y][x + con].z * win->sc_z + offset_y;
			line->x1 = win->map[y][x + 1].x * win->sc_x + offset_x;
			line->y2 = win->map[y][x].y * win->sc_y
					- win->map[y][x].z * win->sc_z;
			line->x2 = win->map[y][x].x * win->sc_x;
			line->end_y = line->y2 + offset_y;
			line->end_x = line->x2 + offset_x;
			if (x < win->map_cols - 1)
				draw_line(win, line, line->y1, line->x1, win->map[y][x].color);
			if (y < win->map_rows - 1)
				draw_line(win, line,
				 win->map[y + 1][x].y * win->sc_y
					- win->map[y + con][x].z * win->sc_z + offset_y,
					 win->map[y + 1][x].x * win->sc_x + offset_x, win->map[y][x].color);
		}
}