/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:59:52 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/31 19:23:43 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "math.h"

static void	rotate_y(t_win *win, size_t x, size_t y, int new_angle)
{
	double tmp_y;
	double tmp_x;
	double tmp_z;
	double angle;

	if (!win)
		return ;
	win->map[y][x].x -= win->param->centr_x;
	win->map[y][x].y -= win->param->centr_y;
	angle = new_angle * PI / 180;
	tmp_x = win->map[y][x].x;
	tmp_y = win->map[y][x].y * cos(angle) + win->map[y][x].z * sin(angle);
	tmp_z = -win->map[y][x].y * sin(angle) + win->map[y][x].z * cos(angle);
	tmp_x += win->param->centr_x;
	tmp_y += win->param->centr_y;
	win->map[y][x].x = tmp_x;
	win->map[y][x].y = tmp_y;
	win->map[y][x].z = tmp_z;
}

static void	rotate_x(t_win *win, size_t x, size_t y, int new_angle)
{
	double tmp_y;
	double tmp_x;
	double tmp_z;
	double angle;

	if (!win)
		return ;
	win->map[y][x].x -= win->param->centr_x;
	win->map[y][x].y -= win->param->centr_y;
	angle = new_angle * PI / 180;
	tmp_x = win->map[y][x].x * cos(angle) + win->map[y][x].z * sin(angle);
	tmp_y = win->map[y][x].y;
	tmp_z = -win->map[y][x].x * sin(angle) + win->map[y][x].z * cos(angle);
	tmp_x += win->param->centr_x;
	tmp_y += win->param->centr_y;
	win->map[y][x].x = tmp_x;
	win->map[y][x].y = tmp_y;
	win->map[y][x].z = tmp_z;
}

static void	rotate_z(t_win *win, size_t x, size_t y, int new_angle)
{
	double tmp_y;
	double tmp_x;
	double tmp_z;
	double angle;

	if (!win)
		return ;
	win->map[y][x].x -= win->param->centr_x;
	win->map[y][x].y -= win->param->centr_y;
	angle = new_angle * PI / 180;
	tmp_x = win->map[y][x].x * cos(angle) - win->map[y][x].y * sin(angle);
	tmp_y = win->map[y][x].x * sin(angle) + win->map[y][x].y * cos(angle);
	tmp_z = win->map[y][x].z;
	tmp_x += win->param->centr_x;
	tmp_y += win->param->centr_y;
	win->map[y][x].x = tmp_x;
	win->map[y][x].y = tmp_y;
	win->map[y][x].z = tmp_z;
}

void	rotate_map(t_win *win, char axis, int new_angle)
{
	size_t	y;
	size_t	x;

	if (!win)
		return ;
	y = -1;
	while (++y < win->param->rows)
	{
		x = -1;
		while (++x < win->param->cols)
		{
			if (axis == 'y' || axis == 'a')
				rotate_y(win, x, y, new_angle);
			if (axis == 'x' || axis == 'a')
				rotate_x(win, x, y, new_angle);
			if (axis == 'z' || axis == 'a')
				rotate_z(win, x, y, new_angle);
		}
	}
	draw_map(win);
}

void	reset(t_win *win)
{
	size_t	y;
	size_t	x;

	if (!win)
		return ;
	y = -1;
	while (++y < win->param->rows)
	{
		x = -1;
		while (++x < win->param->cols)
		{
			win->map[y][x].x = x;
			win->map[y][x].y = y;
			win->map[y][x].z = win->map[y][x].z_orig;
		}
	}
	win->param->offset_x = DEF_OFFSET_X;
	win->param->offset_y = DEF_OFFSET_Y;
	win->param->sc_x = DEF_SCALE;
	win->param->sc_y = DEF_SCALE;
	win->param->sc_z = DEF_SCALE;
	draw_map(win);
}
