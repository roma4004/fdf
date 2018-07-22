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

void	draw_map_vertical(t_win *win, int shY, int shX, int c)
{
	t_line	*l;
	size_t	y;
	size_t	x;

	if (!win || !(l = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows - 1 && (x = -1))
		while (++x < win->map_cols - 1)
		{
			l->y1 = win->map[y + 1][x].y * win->sc_y
			      - win->map[y + c][x].z * win->sc_z;
			l->x1 = win->map[y + 1][x].x * win->sc_x;
			l->y2 = win->map[y][x].y * win->sc_y
				  - win->map[y][x].z * win->sc_z;
			l->x2 = win->map[y][x].x * win->sc_x;
			l->end_y = shY + l->y2;
			l->end_x = shX + l->x2;
			line(win, l, shY + l->y1, shX + l->x1, win->map[y][x].col);
		}	
}

void	draw_map_backslash(t_win *win, int shY, int shX, int c)
{
	t_line	*l;
	size_t	y;
	size_t	x;

	if (!win || !(l = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows - 1 && (x = -1))
		while (++x < win->map_cols - 1)
		{
			l->y1 = win->map[y + 1][x + 1].y * win->sc_y
				  - win->map[y + c][x + c].z * win->sc_z;
			l->x1 = win->map[y + 1][x + 1].x * win->sc_x;
			l->y2 = win->map[y][x].y * win->sc_y
				  - win->map[y][x].z * win->sc_z;
			l->x2 = win->map[y][x].x * win->sc_x;
			l->end_y = shY + l->y2;
			l->end_x = shX + l->x2;
			line(win, l, shY + l->y1, shX + l->x1, win->map[y][x].col);
		}
}

void	draw_map_horizontal(t_win *win, int shY, int shX, int c)
{
	t_line	*l;
	size_t	y;
	size_t	x;

	if (!win || !(l = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows - 1 && (x = -1))
		while (++x < win->map_cols - 1)
		{
			l->y1 = win->map[y][x + 1].y * win->sc_y
				- win->map[y][x + c].z * win->sc_z;
			l->x1 = win->map[y][x + 1].x * win->sc_x;
			l->y2 = win->map[y][x].y * win->sc_y
				- win->map[y][x].z * win->sc_z;
			l->x2 = win->map[y][x].x * win->sc_x;
			l->end_y = shY + l->y2;
			l->end_x = shX + l->x2;
			line(win, l, shY + l->y1, shX + l->x1, win->map[y][x].col);
		}
}

void	draw_map_slash(t_win *win, int shY, int shX, int c)
{
	t_line	*l;
	size_t	y;
	size_t	x;
	
	if (!win || !(l = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows - 1 && (x = -1))
		while (++x < win->map_cols - 1)
		{
			l->y1 = win->map[y + 1][x].y * win->sc_y
				- win->map[y + c][x].z * win->sc_z;
			l->x1 = win->map[y + 1][x].x * win->sc_x;
			l->y2 = win->map[y][x + 1].y * win->sc_y
				- win->map[y][x + c].z * win->sc_z;
			l->x2 = win->map[y][x + 1].x * win->sc_x;
			l->end_y = shY + l->y2;
			l->end_x = shX + l->x2;
			line(win, l, shY + l->y1, shX + l->x1, win->map[y][x].col);
		}
}

void	draw_map_fdf(t_win *win, int shY, int shX, int c)
{
	t_line	*l;
	size_t	y;
	size_t	x;

	if (!win || !(l = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows && (x = -1))		
		while (++x < win->map_cols)
		{	
			l->y1 = (win->map[y][x + 1].y) * (win->sc_y)
				   - win->map[y][x + c].z * (win->sc_z);
			l->x1 = (win->map[y][x + 1].x) * (win->sc_x);
			l->y2 = win->map[y][x].y * (win->sc_y) 
				  - win->map[y][x].z * (win->sc_z);
			l->x2 = win->map[y][x].x * (win->sc_x);
			l->end_y = shY + l->y2;
			l->end_x = shX + l->x2;
			if (x < win->map_cols - 1)
				line(win, l, shY + l->y1, shX + l->x1, win->map[y][x].col);
			if (y < win->map_rows - 1)
				line(win, l,
					shY + (win->map[y + 1][x].y) * (win->sc_y)
						 - win->map[y + c][x].z * (win->sc_z),						 
					shX + (win->map[y + 1][x].x) * (win->sc_x),	win->map[y][x].col);			
		}
		//-----add l->x3 and l->x3-------------------------
}