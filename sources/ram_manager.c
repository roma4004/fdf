/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:23:50 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/15 16:42:21 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				toggle(int *param)
{
	*param = ((*param == 0) ? 1 : 0);
	return (1);
}

static void		show_errors(t_env *win)
{
	if (win->flags.error_code == MAP_INVALID)
		ft_putstr_fd("MAP_INVALID", 2);
	if (win->flags.error_code == WIDTH_ERR)
		ft_putstr_fd("WIDTH_ERR", 2);
	if (win->flags.error_code == READ_ERR)
		ft_putstr_fd("FILE_ERR", 2);
	if (win->flags.error_code == COLOR_ERR)
		ft_putstr_fd("COLOR_ERR", 2);
	if (win->flags.error_code && errno)
		ft_putstr_fd(" - ", 2);
	if (errno)
		ft_putstr_fd(strerror(errno), 2);
	if (win->flags.error_code || errno)
		ft_putstr_fd("\n", 2);
}

int				exit_x(t_env *win)
{
	size_t	i;

	if (!win)
		return (1);
	if (win->mlx_ptr && win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->map && win->flags.error_code != WIDTH_ERR
				&& win->flags.error_code != MAP_INVALID)
	{
		i = UINT64_MAX;
		while (++i < win->param.rows)
			ft_memdel((void *)&win->map[i]);
		ft_memdel((void *)&win->map);
	}
	show_errors(win);
	exit(0);
}

t_env			*clear_img(t_env *win)
{
	size_t y;
	size_t x;

	y = UINT64_MAX;
	while (++y < WIN_HEIGHT)
	{
		x = UINT64_MAX;
		while (++x < WIN_WIDTH)
			win->buffer[y * WIN_WIDTH + x] = 0;
	}
	return (win);
}

t_env			*init_win(t_env *e)
{
	if (!e)
		return (NULL);
	e->param = (t_param){ WIN_WIDTH, WIN_HEIGHT,
		(t_si_pt){ DEF_OFFSET_X, DEF_OFFSET_Y },
		(t_si_3pt){ DEF_SCALE, DEF_SCALE, DEF_SCALE }, (t_db_2pt){ 0.0f, 0.0f },
		0, 0, 0 };
	e->flags = (t_flags){ 1, 1, 1, 0, 0, 0, 0, 0, 0};
	e->map = NULL;
	e->bits_per_pixel = 0;
	e->size_line = 0;
	e->endian = 0;
	if (!(e->mlx_ptr = mlx_init())
	|| !(e->win_ptr = mlx_new_window(e->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, TITLE))
	|| !(e->img_ptr = mlx_new_image(e->mlx_ptr, WIN_WIDTH, WIN_HEIGHT))
	|| !(e->buffer = (int *)mlx_get_data_addr(e->img_ptr,
						&e->bits_per_pixel, &e->size_line, &e->endian)))
		exit_x(e);
	return (e);
}
