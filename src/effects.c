/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:44:39 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/13 20:30:06 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void draw_map_vertical(t_win *win, t_param *p, int c)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < p->rows - 1 && (x = -1))
		while (++x < p->cols - 1)
		{
			line->color = win->map[y][x].color;
			line->end_x = (int)win->map[y][x].x * p->sc_x;
			line->end_y = (int)win->map[y][x].y * p->sc_y
						- (int)win->map[y][x].z * p->sc_z;
			draw_line(win, line, (int)win->map[y + 1][x].x * p->sc_x,
								(int)win->map[y + 1][x].y * p->sc_y -
								(int)win->map[y + c][x].z * p->sc_z);
		}
	ft_memdel((void *)&line);
	redraw_img(win);
}

void draw_map_backslash(t_win *win, t_param *p, int c)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < p->rows - 1 && (x = -1))
		while (++x < p->cols - 1)
		{
			line->color = win->map[y][x].color;
			line->end_x = (int)win->map[y][x].x * p->sc_x;
			line->end_y = (int)win->map[y][x].y * p->sc_y
						- (int)win->map[y][x].z * p->sc_z;
			draw_line(win, line, (int)win->map[y + 1][x + 1].x * p->sc_x,
								(int)win->map[y + 1][x + 1].y * p->sc_y -
								(int)win->map[y + c][x + c].z * p->sc_z);
		}
	ft_memdel((void *)&line);
	redraw_img(win);
}

void draw_map_horizontal(t_win *win, t_param *p, int c)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < p->rows - 1 && (x = -1))
		while (++x < p->cols - 1)
		{
			line->color = win->map[y][x].color;
			line->end_x = (int)win->map[y][x].x * p->sc_x;
			line->end_y = (int)win->map[y][x].y * p->sc_y
						- (int)win->map[y][x].z * p->sc_z;
			draw_line(win, line, (int)win->map[y][x + 1].x * p->sc_x,
								(int)win->map[y][x + 1].y * p->sc_y -
								(int)win->map[y][x + c].z * p->sc_z);
		}
	ft_memdel((void *)&line);
	redraw_img(win);
}

void draw_map_slash(t_win *win, t_param *p, int c)
{
	t_line	*line;
	size_t	x;
	size_t	y;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < p->rows - 1 && (x = -1))
		while (++x < p->cols - 1)
		{
			line->color = win->map[y][x].color;
			line->end_x = (int)win->map[y][x + 1].x * p->sc_x;
			line->end_y = (int)win->map[y][x + 1].y * p->sc_y
						- (int)win->map[y][x + c].z * p->sc_z;
			draw_line(win, line, (int)win->map[y + 1][x].x * p->sc_x,
								(int)win->map[y + 1][x].y * p->sc_y -
								(int)win->map[y + c][x].z * p->sc_z);
		}
	ft_memdel((void *)&line);
	redraw_img(win);
}

void	draw_map_fdf(t_win *win, t_param *p, int c)
{
	t_line	*line;
	size_t	x;
	size_t	y;

	if (!win || !(line = init_line())
	|| !(y = -1))
		return ;
	while (++y < p->rows && (x = -1))
		while (++x < p->cols)
		{
			line->color = win->map[y][x].color;
			line->end_x = (int)win->map[y][x].x * p->sc_x;
			line->end_y = (int)win->map[y][x].y * p->sc_y
						- (int)win->map[y][x].z * p->sc_z;
			if (x < p->cols - 1)
				draw_line(win, line, (int)win->map[y][x + 1].x * p->sc_x,
									(int)win->map[y][x + 1].y * p->sc_y -
									(int)win->map[y][x + c].z * p->sc_z);
			if (y < p->rows - 1)
				draw_line(win, line, (int)win->map[y + 1][x].x * p->sc_x,
									(int)win->map[y + 1][x].y * p->sc_y -
									(int)win->map[y + c][x].z * p->sc_z);
		}
	ft_memdel((void *)&line);
	redraw_img(win);
}
