/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:23:35 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/22 19:23:36 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
/*
void	draw_map_effects(int st_offset_x)
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
			line->end_y = offset_y +  win->map[y      ][x].y  * (win->sc_y)
			                       -  win->map[y      ][x].z  * (win->sc_z); 
			line->end_x = offset_x +  win->map[y      ][x].x  * (win->sc_x);
			draw_line(win, line, 						  
						  offset_y + (win->map[y - 1  ][x].y) * (win->sc_y)
							       -  win->map[y - con][x].z  * (win->sc_z), 
						  offset_x + (win->map[y - 1  ][x].x) * (win->sc_x), DEF_COLOR);
			x++;
		}
		y++;
	}
}*/