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

void	draw_px_by_map(t_win *win, size_t y, size_t x)
{
	mlx_pixel_put(win->mlx_ptr, win->win_ptr,
		   	win->offset_x + win->map[y][x].x * (win->sc_x),
		   	win->offset_y + win->map[y][x].y * (win->sc_y) 
						- (win->map[y][x].z * win->sc_z),
			win->map[y][x].color);
}

void	draw_line(t_win *win, t_line *line, int y, int x, int color)
{
	//draw_px_by_coord(win, x, y, color);
	//line->d = 0;
	line->dy = (line->end_y - y >= 0 ? 1 : -1);
	line->dx = (line->end_x - x >= 0 ? 1 : -1);
	line->len_y = ft_abs(line->end_y - y);
	line->len_x = ft_abs(line->end_x - x);
	line->len = ft_max(line->len_y, line->len_x);
	if (line->len++ == 0)
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, color);
	line->d = ((line->len_y <= line->len_x) ? -line->len_x : -line->len_y);		
	while (line->len--)
	{
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, color);
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

void	draw_map(t_win *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	if (win->interface_on)
		dislpay_interface(win);
	if (win->fdf_on)
		draw_map_fdf(win, win->offset_y, win->offset_x, win->con_on);
	if (win->ver_on)	
		draw_map_vertical(win, win->offset_y, win->offset_x, win->con_on);
	if (win->sla_on)	
		draw_map_slash(win, win->offset_y, win->offset_x, win->con_on);					
	if (win->hor_on)
		draw_map_horizontal(win, win->offset_y, win->offset_x, win->con_on);
	if (win->bsl_on)
		draw_map_backslash(win, win->offset_y, win->offset_x, win->con_on);
}