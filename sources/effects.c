/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:44:39 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/18 11:54:24 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_map_vertical(t_env *win, int *buf, t_param *p, int c)
{
	t_line	line;
	size_t	y;
	size_t	x;
	t_px	**map;

	if (!win)
		return ;
	y = UINT64_MAX;
	map = win->map;
	while (++y < p->rows - 1)
	{
		x = UINT64_MAX;
		while (++x < p->cols - 1)
		{
			line.color = map[y][x].color;
			line.offset = win->param.offset;
			line.end = (t_si_pt){ (int)(map[y][x].x * p->scale.x),
				(int)(map[y][x].y * p->scale.y - map[y][x].z * p->scale.z) };
			draw_line(buf, &line, (int)(map[y + 1][x].x * p->scale.x),
				(int)(map[y + 1][x].y * p->scale.y
				- map[y + c][x].z * p->scale.z));
		}
	}
	redraw_img(win);
}

void	draw_map_backslash(t_env *win, int *buf, t_param *p, int c)
{
	t_line	line;
	size_t	y;
	size_t	x;
	t_px	**map;

	y = UINT64_MAX;
	map = win->map;
	while (++y < p->rows - 1)
	{
		x = UINT64_MAX;
		while (++x < p->cols - 1)
		{
			line.color = map[y][x].color;
			line.offset = win->param.offset;
			line.end = (t_si_pt){ (int)(map[y][x].x * p->scale.x),
				(int)(map[y][x].y * p->scale.y - map[y][x].z * p->scale.z) };
			draw_line(buf, &line, (int)(map[y + 1][x + 1].x * p->scale.x),
				(int)(map[y + 1][x + 1].y * p->scale.y
				- map[y + c][x + c].z * p->scale.z));
		}
	}
	redraw_img(win);
}

void	draw_map_horizontal(t_env *win, int *buf, t_param *p, int c)
{
	t_line	line;
	size_t	y;
	size_t	x;
	t_px	**map;

	y = UINT64_MAX;
	map = win->map;
	while (++y < p->rows - 1)
	{
		x = UINT64_MAX;
		while (++x < p->cols - 1)
		{
			line.color = map[y][x].color;
			line.offset = win->param.offset;
			line.end = (t_si_pt){ (int)(map[y][x].x * p->scale.x),
				(int)(map[y][x].y * p->scale.y - map[y][x].z * p->scale.z) };
			draw_line(buf, &line, (int)(map[y][x + 1].x * p->scale.x),
				(int)(map[y][x + 1].y * p->scale.y
				- map[y][x + c].z * p->scale.z));
		}
	}
	redraw_img(win);
}

void	draw_map_slash(t_env *win, int *buf, t_param *p, int c)
{
	t_line	line;
	size_t	x;
	size_t	y;
	t_px	**map;

	y = UINT64_MAX;
	map = win->map;
	while (++y < p->rows - 1)
	{
		x = UINT64_MAX;
		while (++x < p->cols - 1)
		{
			line.color = map[y][x].color;
			line.offset = win->param.offset;
			line.end = (t_si_pt){ (int)(map[y][x + 1].x * p->scale.x),
				(int)(map[y][x + 1].y * p->scale.y
				- map[y][x + c].z * p->scale.z) };
			draw_line(buf, &line, (int)(map[y + 1][x].x * p->scale.x),
				(int)(map[y + 1][x].y * p->scale.y
				- map[y + c][x].z * p->scale.z));
		}
	}
	redraw_img(win);
}

void	draw_map_fdf(t_env *win, int *buf, t_param *p, int c)
{
	t_line	line;
	size_t	x;
	size_t	y;
	t_px	**map;

	y = UINT64_MAX;
	map = win->map;
	while ((++y < p->rows) & (x = UINT64_MAX))
		while (++x < p->cols)
		{
			line.color = map[y][x].color;
			line.offset = win->param.offset;
			line.end = (t_si_pt){ (int)(map[y][x].x * p->scale.x),
				(int)(map[y][x].y * p->scale.y - map[y][x].z * p->scale.z) };
			if (x < p->cols - 1)
				draw_line(buf, &line, (int)(map[y][x + 1].x * p->scale.x),
					(int)(map[y][x + 1].y * p->scale.y
					- map[y][x + c].z * p->scale.z));
			if (y < p->rows - 1)
				draw_line(buf, &line, (int)(map[y + 1][x].x * p->scale.x),
					(int)(map[y + 1][x].y * p->scale.y
					- map[y + c][x].z * p->scale.z));
		}
	redraw_img(win);
}
