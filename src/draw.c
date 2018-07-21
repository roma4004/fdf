/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/21 20:44:00 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	ft_abs(double num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}

double	ft_max(double first, double second)
{
	if (first > second)
		return (first);
	return (second);
}

void	draw_px_by_coord(t_win *win, double y, double x, int color)
{
	mlx_pixel_put(win->mlx_ptr, win->win_ptr, y, x, color);
}

void	draw_px_by_map(t_win *win, size_t y, size_t x)
{
	mlx_pixel_put(win->mlx_ptr, win->win_ptr,
		   	win->offset_x + win->map[y][x].x * (win->sc_x),
		   	win->offset_y + win->map[y][x].y * (win->sc_y) 
			    -(win->map[y][x].z * win->sc_z),
				  win->map[y][x].color);
}

void	draw_line(t_win *win, t_line *line, double y, double x, int color)
{
	line->dy = (line->end_y - y >= 0 ? 1 : -1);
	line->dx = (line->end_x - x >= 0 ? 1 : -1);
	line->len_y = ft_abs(line->end_y - y);
	line->len_x = ft_abs(line->end_x - x);
	line->len = ft_max(line->len_y, line->len_x);
	if (line->len++ == 0)
		draw_px_by_coord(win, y, x, color);
	line->d = ((line->len_y <= line->len_x) ? -line->len_x : -line->len_y);		
	while (line->len--)
	{
		draw_px_by_coord(win, x, y, color);
		line->d += 2 * ((line->len_y <= line->len_x) ? line->len_y : line->len_x);
		if (line->len_y <= line->len_x)
			x += line->dx;			
		else
			y += line->dy;
		if (line->d > 0)
		{
			line->d -= 2 * ((line->len_y <= line->len_x) ? line->len_x : line->len_y);
			if (line->len_y <= line->len_x)
				y += line->dy;
			else
				x += line->dx;
		}
	}
}