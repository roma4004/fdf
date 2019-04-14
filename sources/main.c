/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/18 19:45:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_env	*init_win(t_env *e)
{
	if (!e)
		return (NULL);
	e->param = (t_param){ WIN_WIDTH, WIN_HEIGHT,
		(t_si_pt){ DEF_OFFSET_X, DEF_OFFSET_Y },
		(t_si_3pt){ DEF_SCALE, DEF_SCALE, DEF_SCALE },
		(t_db_2pt){ 0.0f, 0.0f },
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

void			show_interface(t_env *win)
{
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 10, DEF_COLOR,
		"move            : arrows left, up, down, right");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 30, DEF_COLOR,
		"zoom all        : -, + or mouse scroll");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 50, DEF_COLOR,
		"zoom only Z     : 9, 0 or numpad +, -");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 70, DEF_COLOR,
		"interface       : 8 or numpad 8");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 90, DEF_COLOR,
		"rotate X,Y,Z(+-): QA, WS, ED");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 110, DEF_COLOR,
		"next style      : enter (hold to animate)");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 130, DEF_COLOR,
		"reset           : R");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 150, DEF_COLOR,
		"add visual style: 1..7 or numpad 1..7 (|, /, -, \\, fdf, layer, dot)");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 170, DEF_COLOR,
		"exit the program: esc or hit the (x) at the corner window");
}

int				exit_x(t_env *e)
{
	size_t	i;
	int		err;
	char	*msg;

	err = e->flags.error_code;
	if (e->mlx_ptr && e->win_ptr)
		mlx_destroy_window(e->mlx_ptr, e->win_ptr);
	if (e->map && err != WIDTH_ERR && (err != MAP_INVALID) & (i = UINT64_MAX))
	{
		while (++i < e->param.rows)
			ft_memdel((void **)&e->map[i]);
		ft_memdel((void **)&e->map);
	}
	if (((err == MAP_INVALID) && (msg = "MAP_INVALID"))
	|| ((err == WIDTH_ERR) && (msg = "WIDTH_ERR"))
	|| ((err == READ_ERR) && (msg = "FILE_ERR"))
	|| ((err == COLOR_ERR) && (msg = "COLOR_ERR")))
		ft_putstr_fd(msg, 2);
	if (err && errno && (msg = " - "))
		ft_putstr_fd(msg, 2);
	if (errno && (msg = strerror(errno)))
		ft_putstr_fd(msg, 2);
	if (err || errno)
		ft_putstr_fd("\n", 2);
	exit(0);
}

int				main(int argc, char **argv)
{
	t_env	win;

	if (argc == 2 && (init_win(&win)))
	{
		if (!parse_map(argv[1], &win))
		{
			draw_map(&win, win.map, win.buffer, win.param);
			mlx_hook(win.win_ptr, 17, 1L << 17, exit_x, &win);
			mlx_hook(win.win_ptr, 2, 5, deal_keyboard, &win);
			mlx_mouse_hook(win.win_ptr, deal_mouse, &win);
			mlx_loop(win.mlx_ptr);
		}
		else
			exit_x(&win);
	}
	else
	{
		ft_putstr("Usage: ./fdf map.fdf\n");
		exit(1);
	}
	return (0);
}
