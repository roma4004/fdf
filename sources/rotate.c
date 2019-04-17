/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:59:52 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/17 15:39:24 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "math.h"

static t_db_3pt		rotate_y(t_db_3pt pt, double angle)
{
	return ((t_db_3pt){ pt.x,
						pt.y * cos(angle) + pt.z * sin(angle),
						-pt.y * sin(angle) + pt.z * cos(angle) });
}

static t_db_3pt		rotate_x(t_db_3pt pt, double angle)
{
	return ((t_db_3pt){ pt.x * cos(angle) + pt.z * sin(angle),
						pt.y,
						-pt.x * sin(angle) + pt.z * cos(angle) });
}

static t_db_3pt		rotate_z(t_db_3pt pt, double angle)
{
	return ((t_db_3pt){ pt.x * cos(angle) - pt.y * sin(angle),
						pt.x * sin(angle) + pt.y * cos(angle),
						pt.z });
}

void				rotate_map(t_env *e, t_px **map, char axis, double angle)
{
	const double	angle_radian = angle * PI / 180;
	const t_db_2pt	center = e->param.center;
	t_db_3pt		pt;
	size_t			y;
	size_t			x;

	y = UINT64_MAX;
	while (e->param.rows > ++y)
	{
		x = UINT64_MAX;
		while (e->param.cols > ++x)
		{
			pt = map[y][x].pt;
			pt = (t_db_3pt){ pt.x - center.x, pt.y - center.y, pt.z };
			if ('y' == axis)
				pt = rotate_y(pt, angle_radian);
			if ('x' == axis)
				pt = rotate_x(pt, angle_radian);
			if ('z' == axis)
				pt = rotate_z(pt, angle_radian);
			map[y][x].pt = (t_db_3pt){ pt.x + center.x, pt.y + center.y, pt.z };
		}
	}
	draw_map(e, map, e->buffer, e->param);
}

void				reset(t_env *e)
{
	size_t	y;
	size_t	x;

	if (!e)
		return ;
	y = UINT64_MAX;
	while (e->param.rows > ++y)
	{
		x = UINT64_MAX;
		while (e->param.cols > ++x)
			e->map[y][x].pt = (t_db_3pt){ x, y, e->map[y][x].z_orig };
	}
	e->param.move = (t_si_pt){ DEF_OFFSET_X, DEF_OFFSET_Y };
	e->param.scale = (t_si_3pt){ DEF_SCALE, DEF_SCALE, DEF_SCALE };
	draw_map(e, e->map, e->buffer, e->param);
}
