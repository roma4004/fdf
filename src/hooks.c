/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/28 18:16:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		exit_x(t_win *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	free_win(win);
	exit(0);
}

void	map_offset(t_win *win, int offset_x, int offset_y)
{
	win->param->offset_x += offset_x;
	win->param->offset_y += offset_y;
	draw_map(win);
}

void	zoom_offset(t_win *win, int zoom_offset, int only_z)
{
	if (only_z == 0)
	{
		if (win->param->sc_x + zoom_offset >= 0)
			win->param->sc_x += zoom_offset;
		if (win->param->sc_y + zoom_offset >= 0)
			win->param->sc_y += zoom_offset;
		if (win->param->sc_z + zoom_offset >= 0)
			win->param->sc_z += zoom_offset;
	}
	else
		win->param->sc_z += zoom_offset;
	draw_map(win);
}

void	toggles(t_win *win, int key)
{
	if (key == 1)
		toggle_param(&win->flags->ver_on);
	if (key == 2)
		toggle_param(&win->flags->sla_on);
	if (key == 3)
		toggle_param(&win->flags->hor_on);
	if (key == 4)
		toggle_param(&win->flags->bsl_on);
	if (key == 5)
		toggle_param(&win->flags->fdf_on);
	if (key == 6)
		toggle_param(&win->flags->con_on);
	if (key == 7)
		toggle_param(&win->flags->dot_on);
	if (key == 8)
		toggle_param(&win->flags->interface_on);
	draw_map(win);
}

void	animate(t_win *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	if (win->flags->interface_on)
		show_interface(win);
	if (++win->param->frame_cnt == 4)
		win->param->frame_cnt = 0;
	if (win->param->frame_cnt == 0)
		draw_map_vertical(win, win->flags->con_on);
	else if (win->param->frame_cnt == 1)
		draw_map_slash(win, win->flags->con_on);
	else if (win->param->frame_cnt == 2)
		draw_map_horizontal(win, win->flags->con_on);
	else if (win->param->frame_cnt == 3)
		draw_map_backslash(win, win->flags->con_on);
}
