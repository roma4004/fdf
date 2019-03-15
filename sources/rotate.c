/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:59:52 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/15 16:14:07 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "math.h"

static void	rotate_y(t_env *win, t_px *px, int new_angle)
{
	t_db_3pt	tmp;
	double		angle;

	if (!win)
		return ;
	px->x -= win->param.centr.x;
	px->y -= win->param.centr.y;
	angle = new_angle * PI / 180;
	tmp.x = px->x;
	tmp.y = px->y * cos(angle)
			+ px->z * sin(angle);
	tmp.z = -px->y * sin(angle)
			+ px->z * cos(angle);
	tmp.x += win->param.centr.x;
	tmp.y += win->param.centr.y;
	px->x = tmp.x;
	px->y = tmp.y;
	px->z = tmp.z;
}

static void	rotate_x(t_env *win, t_px *px, int new_angle)
{
	t_db_3pt	tmp;
	double		angle;

	if (!win)
		return ;
	px->x -= win->param.centr.x;
	px->y -= win->param.centr.y;
	angle = new_angle * PI / 180;
	tmp.x = px->x * cos(angle)
			+ px->z * sin(angle);
	tmp.y = px->y;
	tmp.z = -px->x * sin(angle)
			+ px->z * cos(angle);
	tmp.x += win->param.centr.x;
	tmp.y += win->param.centr.y;
	px->x = tmp.x;
	px->y = tmp.y;
	px->z = tmp.z;
}

static void	rotate_z(t_env *win, t_px *px, int new_angle)
{
	t_db_3pt	tmp;
	double		angle;

	if (!win)
		return ;
	px->x -= win->param.centr.x;
	px->y -= win->param.centr.y;
	angle = new_angle * PI / 180;
	tmp.x = px->x * cos(angle)
			- px->y * sin(angle);
	tmp.y = px->x * sin(angle)
			+ px->y * cos(angle);
	tmp.z = px->z;
	tmp.x += win->param.centr.x;
	tmp.y += win->param.centr.y;
	px->x = tmp.x;
	px->y = tmp.y;
	px->z = tmp.z;
}

void		rotate_map(t_env *win, char axis, int new_angle)
{
	t_ui_pt pt;

	if (!win)
		return ;
	pt.y = 0;
	while (pt.y < win->param.rows)
	{
		pt.x = 0;
		while (pt.x < win->param.cols)
		{
			if (axis == 'y' || axis == 'a')
				rotate_y(win, &win->map[pt.y][pt.x], new_angle);
			if (axis == 'x' || axis == 'a')
				rotate_x(win, &win->map[pt.y][pt.x], new_angle);
			if (axis == 'z' || axis == 'a')
				rotate_z(win, &win->map[pt.y][pt.x], new_angle);
			pt.x++;
		}
		pt.y++;
	}
	draw_map(win);
}

void		reset(t_env *win)
{
	size_t	y;
	size_t	x;

	if (!win)
		return ;
	y = 0;
	while (y < win->param.rows)
	{
		x = 0;
		while (x < win->param.cols)
		{
			win->map[y][x].x = x;
			win->map[y][x].y = y;
			win->map[y][x].z = win->map[y][x].z_orig;
			x++;
		}
		y++;
	}
	win->param.offset = (t_si_pt){ DEF_OFFSET_X, DEF_OFFSET_Y };
	win->param.scale = (t_si_3pt){ DEF_SCALE, DEF_SCALE, DEF_SCALE };
	draw_map(win);
}
