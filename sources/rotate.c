/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:59:52 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/14 22:34:13 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "math.h"

static t_db_3pt		rotate_y(t_db_3pt pt, int new_angle)
{
	const double	angle = new_angle * PI / 180;

	return ((t_db_3pt){ pt.x,
						pt.y * cos(angle) + pt.z * sin(angle),
						-pt.y * sin(angle) + pt.z * cos(angle) });

}

static t_db_3pt		rotate_x(t_db_3pt pt, int new_angle)
{
	const double	angle = new_angle * PI / 180;

	return ((t_db_3pt){ pt.x * cos(angle) + pt.z * sin(angle),
						pt.y,
						-pt.x * sin(angle) + pt.z * cos(angle) });
}

static t_db_3pt		rotate_z(t_db_3pt pt, int new_angle)
{
	const double	angle = new_angle * PI / 180;

	return ((t_db_3pt){ pt.x * cos(angle) - pt.y * sin(angle),
						pt.x * sin(angle) + pt.y * cos(angle),
						pt.z });
}

void		rotate_map(t_env *win, char axis, int new_angle)
{
	size_t	y;
	size_t	x;

	if (!win)
		return ;
	y = UINT64_MAX;
	while (win->param.rows > ++y)
	{
		x = UINT64_MAX;
		while (win->param.cols > ++x)
		{
			win->map[y][x].pt.x -= win->param.centr.x;
			win->map[y][x].pt.y -= win->param.centr.y;
			if (axis == 'y' || axis == 'a')
				win->map[y][x].pt = rotate_y(win->map[y][x].pt, new_angle);
			if (axis == 'x' || axis == 'a')
				win->map[y][x].pt = rotate_x(win->map[y][x].pt, new_angle);
			if (axis == 'z' || axis == 'a')
				win->map[y][x].pt = rotate_z(win->map[y][x].pt, new_angle);
			win->map[y][x].pt.x += win->param.centr.x;
			win->map[y][x].pt.y += win->param.centr.y;
		}
	}
	draw_map(win, win->map, win->buffer, win->param);
}

void		reset(t_env *win)
{
	size_t	y;
	size_t	x;

	if (!win)
		return ;
	y = UINT64_MAX;
	while (win->param.rows > ++y)
	{
		x = UINT64_MAX;
		while (win->param.cols > ++x)
			win->map[y][x].pt = (t_db_3pt){ x, y, win->map[y][x].z_orig };
	}
	win->param.offset = (t_si_pt){ DEF_OFFSET_X, DEF_OFFSET_Y };
	win->param.scale = (t_si_3pt){ DEF_SCALE, DEF_SCALE, DEF_SCALE };
	draw_map(win, win->map, win->buffer, win->param);
}
