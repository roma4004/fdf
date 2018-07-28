/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/28 18:17:42 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_line	*init_line(void)
{
	t_line *new_line;

	new_line = NULL;
	if ((new_line = (t_line *)malloc(sizeof(t_line))))
	{
		new_line->end_x = 0;
		new_line->end_y = 0;
		new_line->len_y = 0;
		new_line->len_x = 0;
		new_line->len = 0;
		new_line->dy = 0;
		new_line->dx = 0;
		new_line->d = 0;
	}
	return (new_line);
}

t_param	*init_param(void)
{
	t_param *new_param;

	new_param = NULL;
	if ((new_param = (t_param *)malloc(sizeof(t_param))))
	{
		new_param->rows = 0;
		new_param->cols = 0;
		new_param->width = WIN_WIDTH;
		new_param->height = WIN_HEIGHT;
		new_param->frame_cnt = 0;
		new_param->offset_x = DEF_OFFSET_X;
		new_param->offset_y = DEF_OFFSET_Y;
		new_param->sc_x = DEF_SCALE;
		new_param->sc_y = DEF_SCALE;
		new_param->sc_z = DEF_SCALE;
		new_param->centr_x = 0;
		new_param->centr_y = 0;
	}
	return (new_param);
}

t_flags	*init_flags(void)
{
	t_flags	*new_flags;

	if ((new_flags = (t_flags *)malloc(sizeof(t_flags))))
	{
		new_flags->ver_on = 0;
		new_flags->sla_on = 0;
		new_flags->hor_on = 0;
		new_flags->bsl_on = 0;
		new_flags->fdf_on = 1;
		new_flags->con_on = 1;
		new_flags->dot_on = 1;
		new_flags->interface_on = 1;
		new_flags->error_code = 0;
		return (new_flags);
	}
	return (NULL);
}

t_win	*init_win(void)
{
	t_win	*new_win;

	new_win = NULL;
	if (!(new_win = (t_win *)malloc(sizeof(t_win)))
	|| !(new_win->param = init_param())
	|| !(new_win->flags = init_flags())
	|| !(new_win->mlx_ptr = mlx_init())
	|| !(new_win->win_ptr = mlx_new_window(new_win->mlx_ptr,
											new_win->param->width,
											new_win->param->height, WIN_NAME)))
		free_win(new_win);
	return (new_win);
}
