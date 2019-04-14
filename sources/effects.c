/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:44:39 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/14 22:17:19 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	conn_vertical(t_px **map, int *buffer, t_param p, int c)
{
	t_line	line;
	size_t	y;
	size_t	x;

	if (!map || !(*map) || !buffer)
		return ;
	y = UINT64_MAX;
	while (++y < p.rows - 1)
	{
		x = UINT64_MAX;
		while (++x < p.cols - 1)
		{
			line.color = map[y][x].color;
			line.offset = p.offset;
			line.end = (t_si_pt){ (int)(map[y][x].pt.x * p.scale.x),
									(int)(map[y][x].pt.y * p.scale.y
										- map[y][x].pt.z * p.scale.z) };
			draw_line(buffer, &line, (int)(map[y + 1][x].pt.x * p.scale.x),
									(int)(map[y + 1][x].pt.y * p.scale.y
										- map[y + c][x].pt.z * p.scale.z));
		}
	}
}

void	conn_backslash(t_px **map, int *buffer, t_param p, int c)
{
	t_line	line;
	size_t	y;
	size_t	x;

	if (!map || !(*map) || !buffer)
		return ;
	y = UINT64_MAX;
	while (++y < p.rows - 1)
	{
		x = UINT64_MAX;
		while (++x < p.cols - 1)
		{
			line.color = map[y][x].color;
			line.offset = p.offset;
			line.end = (t_si_pt){ (int)(map[y][x].pt.x * p.scale.x),
									(int)(map[y][x].pt.y * p.scale.y
										- map[y][x].pt.z * p.scale.z) };
			draw_line(buffer, &line, (int)(map[y + 1][x + 1].pt.x * p.scale.x),
									(int)(map[y + 1][x + 1].pt.y * p.scale.y
										- map[y + c][x + c].pt.z * p.scale.z));
		}
	}
}

void	conn_horizontal(t_px **map, int *buffer, t_param p, int c)
{
	t_line	line;
	size_t	y;
	size_t	x;

	if (!map || !(*map) || !buffer)
		return ;
	y = UINT64_MAX;
	while (++y < p.rows - 1)
	{
		x = UINT64_MAX;
		while (++x < p.cols - 1)
		{
			line.color = map[y][x].color;
			line.offset = p.offset;
			line.end = (t_si_pt){ (int)(map[y][x].pt.x * p.scale.x),
									(int)(map[y][x].pt.y * p.scale.y
										- map[y][x].pt.z * p.scale.z) };
			draw_line(buffer, &line, (int)(map[y][x + 1].pt.x * p.scale.x),
									(int)(map[y][x + 1].pt.y * p.scale.y
										- map[y][x + c].pt.z * p.scale.z));
		}
	}
}

void	conn_slash(t_px **map, int *buffer, t_param p, int c)
{
	t_line	line;
	size_t	x;
	size_t	y;

	if (!map || !(*map) || !buffer)
		return ;
	y = UINT64_MAX;
	while (++y < p.rows - 1)
	{
		x = UINT64_MAX;
		while (++x < p.cols - 1)
		{
			line.color = map[y][x].color;
			line.offset = p.offset;
			line.end = (t_si_pt){ (int)(map[y][x + 1].pt.x * p.scale.x),
									(int)(map[y][x + 1].pt.y * p.scale.y
										- map[y][x + c].pt.z * p.scale.z) };
			draw_line(buffer, &line, (int)(map[y + 1][x].pt.x * p.scale.x),
									(int)(map[y + 1][x].pt.y * p.scale.y
										- map[y + c][x].pt.z * p.scale.z));
		}
	}
}

void	conn_fdf(t_px **map, int *buffer, t_param p, int c)
{
	t_line	line;
	size_t	x;
	size_t	y;

	if (!map || !(*map) || !buffer)
		return ;
	y = UINT64_MAX;
	while ((p.rows > ++y) & (x = UINT64_MAX))
		while (p.cols > ++x)
		{
			line.color = map[y][x].color;
			line.offset = p.offset;
			line.end = (t_si_pt){ (int)(map[y][x].pt.x * p.scale.x),
									(int)(map[y][x].pt.y * p.scale.y
										- map[y][x].pt.z * p.scale.z) };
			if (x < p.cols - 1)
				draw_line(buffer, &line, (int)(map[y][x + 1].pt.x * p.scale.x),
										(int)(map[y][x + 1].pt.y * p.scale.y
											- map[y][x + c].pt.z * p.scale.z));
			if (y < p.rows - 1)
				draw_line(buffer, &line, (int)(map[y + 1][x].pt.x * p.scale.x),
										(int)(map[y + 1][x].pt.y * p.scale.y
											- map[y + c][x].pt.z * p.scale.z));
		}
}
