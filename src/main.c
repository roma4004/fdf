/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/31 18:12:53 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	show_errors(t_win *win)
{
	ft_putstr_to("error_code: ", 2);
	ft_putstr_to(ft_itoa(win->flags->error_code), 2);
	ft_putstr_to("\nlegend:\n"
		"\tMAP_INVALID = 404,\n"
		"\tWIDTH_ERR = 405,\n"
		"\tFILE_ERR = 406\n"
		"\tCOLOR_ERR = 407", 2);
}

int			main(int argc, char **argv)
{
	t_win	*win;

	if (argc == 2 && (win = init_win()))
	{
		if (parse_map(argv[1], win))
		{
			draw_map(win);
			mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, win);
			mlx_hook(win->win_ptr, 2, 5, deal_keyboard, win);
			mlx_mouse_hook(win->win_ptr, deal_mouse, win);
			mlx_loop(win->mlx_ptr);
		}
		else
		{
			show_errors(win);
			exit_x(win);
		}
	}
	else
	{
		ft_putstr("Usage: ./fdf map.fdf\n");
		exit(1);
	}
	return (0);
}
