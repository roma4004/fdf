/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/18 12:58:05 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_env	*init_win(t_env *e)
{
	if (!e)
		return (NULL);
	e->param = (t_param){ WIN_WIDTH, WIN_HEIGHT,
		(t_si_2pt){ DEF_OFFSET_X, DEF_OFFSET_Y },
		(t_si_3pt){ DEF_SCALE, DEF_SCALE, DEF_SCALE },
		(t_db_2pt){ 0.0, 0.0 },
		0, 0, 0 };
	e->flags = (t_flags){ 1, 1, 1, 0, 0, 0, 0, 0, 0 };
	e->map = NULL;
	if (!(e->mlx_ptr = mlx_init())
	|| !(e->win_ptr = mlx_new_window(e->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, TITLE))
	|| !(e->img_ptr = mlx_new_image(e->mlx_ptr, WIN_WIDTH, WIN_HEIGHT))
	|| !(e->buffer = (int *)mlx_get_data_addr(e->img_ptr, &e->bits_per_pixel,
															&e->size_line,
															&e->endian)))
		exit_x(e);
	return (e);
}

int				exit_x(t_env *e)
{
	const int	error_code = e->flags.error_code;
	size_t		i;
	char		*msg;

	if (e->mlx_ptr && e->win_ptr)
		mlx_destroy_window(e->mlx_ptr, e->win_ptr);
	if (e->map && WIDTH_ERR != error_code && MAP_INVALID != error_code)
	{
		i = UINT64_MAX;
		while (e->param.rows > ++i)
			ft_memdel((void **)&e->map[i]);
		ft_memdel((void **)&e->map);
	}
	if ((MAP_INVALID == error_code && (msg = "MAP_INVALID"))
	|| (WIDTH_ERR == error_code && (msg = "WIDTH_ERR"))
	|| (READ_ERR == error_code && (msg = "FILE_ERR"))
	|| (COLOR_ERR == error_code && (msg = "COLOR_ERR")))
		ft_putstr_fd(msg, 2);
	if (errno && error_code && (msg = " - "))
		ft_putstr_fd(msg, 2);
	if (errno && (msg = strerror(errno)))
		ft_putstr_fd(msg, 2);
	if (errno || error_code)
		ft_putstr_fd("\n", 2);
	exit(0);
}

int				main(int argc, char **argv)
{
	t_env	e;

	if (argc == 2 && (init_win(&e)))
	{
		if (!parse_file(&e, argv[1]))
		{
			draw_map(&e, e.map, e.buffer, e.param);
			mlx_hook(e.win_ptr, 17, 1L << 17, exit_x, &e);
			mlx_hook(e.win_ptr, 2, 5, deal_keyboard, &e);
			mlx_mouse_hook(e.win_ptr, deal_mouse, &e);
			mlx_loop(e.mlx_ptr);
		}
		else
			exit_x(&e);
	}
	else
	{
		ft_putstr("Usage: ./fdf map.fdf\n");
		exit(1);
	}
	return (0);
}
