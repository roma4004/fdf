/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/22 17:23:20 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void     init_win(t_win *win)
{
	if (win != NULL)
	{
        win->width = WIN_WIDTH;
		win->height = WIN_HEIGHT;
		win->offset_x = WIN_OFFSET_X;
		win->offset_y = WIN_OFFSET_Y;
		win->sc_x = WIN_SCALE;
		win->sc_y = WIN_SCALE;
		win->sc_z = WIN_SCALE;
		win->frame_cnt = 0;
		win->ver_on = 0;
		win->sla_on = 0;
		win->hor_on = 0;
		win->bsl_on = 0;
		win->fdf_on = 1;
		win->con_on = 1;
		win->interface_on = 1;		
		win->mlx_ptr = mlx_init();
		win->win_ptr = mlx_new_window(win->mlx_ptr, win->width, win->height, WIN_NAME);
        //return (1);
	}
    //return (0);
}
t_px	*init_px(void)
{
	t_px *new_px;

	if ((new_px = (t_px *)malloc(sizeof(t_px))))
	{
		new_px->x = 0;
		new_px->y = 0;
		new_px->z = 0;
		new_px->z_orig = 0;
		new_px->color = 0;
		new_px->alpha = 0;
		return (new_px);
	}
	return (NULL);
}

void	init_line(t_line *line)
{
	if (line != NULL)
	{
		line->start_x = 0;
		line->start_y = 0;
		line->start_x = 0;
		line->start_y = 0;
		line->end_x = 0;
		line->end_y = 0;
		line->len_y = 0;
		line->len_x = 0;
		line->len = 0;
		line->dy = 0;
		line->dx = 0;
		line->y1 = 0;
		line->x1 = 0;
		line->y2 = 0;
		line->x2 = 0;
		line->d = 0;
	}
}