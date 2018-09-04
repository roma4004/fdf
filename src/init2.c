/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 20:28:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/22 20:45:43 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_img	*init_img(void *mlx_ptr, int width, int height)
{
	t_img	*new_img;

	if (!mlx_ptr)
		return (NULL);
	if ((new_img = (t_img *)malloc(sizeof(t_img))))
	{
		//new_img->ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
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