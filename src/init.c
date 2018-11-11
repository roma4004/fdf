/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/25 14:49:29 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_img			*init_img(void *mlx_ptr, int width, int height)
{
	t_img	*new_img;

	if (!mlx_ptr)
		return (NULL);
	if ((new_img = (t_img *)malloc(sizeof(t_img))))
	{
		new_img->bits_per_pixel = 0;
		new_img->size_line = 0;
		new_img->endian = 0;
		new_img->img_ptr = mlx_new_image(mlx_ptr, width, height);
		new_img->data = (int *)mlx_get_data_addr(new_img->img_ptr,
												&new_img->size_line,
												&new_img->bits_per_pixel,
												&new_img->endian);
	}
	return (new_img);
}

static t_param	*init_param(void)
{
	t_param *new_param;

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
		new_param->centr_x = 0.0;
		new_param->centr_y = 0.0;
	}
	return (new_param);
}

static t_flags	*init_flags(void)
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
		new_flags->dot_on = 0;
		new_flags->interface_on = 1;
		new_flags->error_code = 0;
	}
	return (new_flags);
}

t_win			*init_win(void)
{
	t_win	*new_win;

	if (!(new_win = (t_win *)malloc(sizeof(t_win)))
	|| (new_win->map = NULL)
	|| !(new_win->param = init_param())
	|| !(new_win->flags = init_flags())
	|| !(new_win->mlx_ptr = mlx_init())
	|| !(new_win->win_ptr = mlx_new_window(new_win->mlx_ptr,
										WIN_WIDTH, WIN_HEIGHT, WIN_NAME))
	|| !(new_win->img = init_img(new_win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		free_win(new_win);
	return (new_win);
}
