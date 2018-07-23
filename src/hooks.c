/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/17 15:26:15 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

void    map_offset(t_win *win, int offset_y, int offset_x)
{
    mlx_clear_window(win->mlx_ptr, win->win_ptr);
    win->offset_y += offset_y;
    win->offset_x += offset_x;
    draw_map(win);
}

void    zoom_offset(t_win *win, int zoom_offset, int only_z)
{
    mlx_clear_window(win->mlx_ptr, win->win_ptr);
    if (only_z == 0)
    {
        win->sc_y += zoom_offset; printf("sc_y: %d\n", win->sc_y);
        win->sc_x += zoom_offset; printf("sc_x: %d\n", win->sc_x);
    }
    win->sc_z += zoom_offset; printf("sc_z: %d\n", win->sc_z);
    draw_map(win);
}

void    numpads(t_win *win, int key)
{
    mlx_clear_window(win->mlx_ptr, win->win_ptr);
    if (key == 1)
        toggle_param(&win->ver_on);
    if (key == 2)
        toggle_param(&win->sla_on);
    if (key == 3)
        toggle_param(&win->hor_on);
    if (key == 4)
        toggle_param(&win->bsl_on);
    if (key == 5)
        toggle_param(&win->fdf_on);
    if (key == 6)
        toggle_param(&win->con_on);
    draw_map(win);
}

void    animate(t_win *win)
{
    mlx_clear_window(win->mlx_ptr, win->win_ptr);
    if (++win->frame_cnt == 4)
        win->frame_cnt = 0;
    if (win->frame_cnt == 0)
         draw_map_vertical(win, win->offset_y, win->offset_x, win->con_on);
	else if (win->frame_cnt == 1)
        draw_map_slash(win, win->offset_y, win->offset_x, win->con_on);
	else if (win->frame_cnt == 2)
        draw_map_horizontal(win, win->offset_y, win->offset_x, win->con_on);
	else if (win->frame_cnt == 3)
        draw_map_backslash(win, win->offset_y, win->offset_x, win->con_on);
}