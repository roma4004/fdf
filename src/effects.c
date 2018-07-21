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

void	draw_line_map_vertical(t_win *win, int offset_y, int offset_x, int con_layers)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
	y = 1;
	while (y < win->map_rows)
	{
		x = 1;
		while (x < win->map_cols)
		{
			line->end_y = offset_y +  win->map[y             ][x].y  * (win->sc_y)
			                       -  win->map[y             ][x].z  * (win->sc_z); 
			line->end_x = offset_x +  win->map[y             ][x].x  * (win->sc_x);
			draw_line(win, line, 						  
						  offset_y + (win->map[y - 1         ][x].y) * (win->sc_y)
							       -  win->map[y - con_layers][x].z  * (win->sc_z), 
						  offset_x + (win->map[y - 1         ][x].x) * (win->sc_x), DEF_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_line_map_backslash(t_win *win, int offset_y, int offset_x, int con_layers)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
	y = 1;
	while (y < win->map_rows)
	{
		x = 1;
		while (x < win->map_cols)
		{
			line->end_y = offset_y +  win->map[y             ][x             ].y  * (win->sc_y) 
								   -  win->map[y             ][x             ].z  * (win->sc_z); 
			line->end_x = offset_x +  win->map[y             ][x             ].x  * (win->sc_x);
			draw_line(win, line, 
						  offset_y + (win->map[y - 1         ][x - 1         ].y ) * (win->sc_y)
							       -  win->map[y - con_layers][x - con_layers].z   * (win->sc_z),
						  offset_x + (win->map[y - 1         ][x - 1         ].x ) * (win->sc_x),  DEF_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_line_map_horizontal(t_win *win, int offset_y, int offset_x, int con_layers)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
	y = 1;
	while (y < win->map_rows)
	{
		x = 1;
		while (x < win->map_cols)
		{
			line->end_y = offset_y +  win->map[y    ][x             ].y  * (win->sc_y)
			                       -  win->map[y    ][x             ].z  * (win->sc_z); 
			line->end_x = offset_x +  win->map[y    ][x             ].x  * (win->sc_x);
			draw_line(win, line, 						  
						  offset_y + (win->map[y    ][x - 1         ].y) * (win->sc_y)
								   -  win->map[y    ][x - con_layers].z  * (win->sc_z), 
						  offset_x + (win->map[y    ][x - 1         ].x) * (win->sc_x), DEF_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_line_map_slash(t_win *win, int offset_y, int offset_x, int con_layers)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
	y = 1;
	while (y < win->map_rows)
	{
		x = 1;
		while (x < win->map_cols)
		{
			line->end_y = offset_y +  win->map[y             ][x - 1         ].y  * (win->sc_y)
			                       -  win->map[y             ][x - con_layers].z  * (win->sc_z); 
			line->end_x = offset_x +  win->map[y             ][x - 1         ].x  * (win->sc_x);
			draw_line(win, line, 						  
						  offset_y + (win->map[y - 1         ][x             ].y) * (win->sc_y)
							       -  win->map[y - con_layers][x             ].z  * (win->sc_z), 
						  offset_x + (win->map[y - 1         ][x             ].x) * (win->sc_x), DEF_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_line_map_fdf(t_win *win)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	if (!(line = (t_line *)malloc(sizeof(t_line))) || !(y = -1))
		return ;
	while (++y < win->map_rows && (x = -1))		
		while (++x < win->map_cols)
		{
			line->end_y = win->offset_y + win->map[y][x].y  * (win->sc_y) 
										- win->map[y][x].z  * (win->sc_z);
			line->end_x = win->offset_x + win->map[y][x].x  * (win->sc_x);
			if (x < win->map_cols - 1)
				draw_line(win, line, 
					win->offset_y + (win->map[y][x + 1].y) * (win->sc_y)
									- win->map[y][x + 1].z * (win->sc_z),
					win->offset_x + (win->map[y][x + 1].x) * (win->sc_x),
									win->map[y][x + 1].color);
			if (y < win->map_rows - 1)
				draw_line(win, line,
					win->offset_y + (win->map[y + 1][x].y) * (win->sc_y)
									- win->map[y + 1][x].z * (win->sc_z),
					win->offset_x + (win->map[y + 1][x].x) * (win->sc_x),
									win->map[y + 1][x].color);			
		}	
}