/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/15 16:41:13 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			is_hex(char ch)
{
	if (ft_isdigit(ch)
	|| (ch >= 'A' && ch <= 'F')
	|| (ch >= 'a' && ch <= 'f'))
		return (1);
	return (0);
}

int			get_col(t_env *win, char *s, size_t *i, size_t max_i)
{
	int		res;
	size_t	j;

	res = DEF_COLOR;
	j = UINT64_MAX;
	if (*i + 3 < max_i && s && s[++j] == ',' && s[++j] == '0' && s[++j] == 'x')
	{
		while (*i + ++j < max_i && is_hex(s[j]))
			if (j > 10)
			{
				win->flags.error_code = COLOR_ERR;
				return (DEF_COLOR);
			}
		(*i) += j;
		res = (int)ft_atol_base(s + 1, 16);
	}
	return (res);
}

void		show_interface(t_env *win)
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

int			main(int argc, char **argv)
{
	t_env	win;

	if (argc == 2 && (init_win(&win)))
	{
		if (parse_map(argv[1], &win))
		{
			draw_map(&win);
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
