/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/05 15:50:43 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	show_errors(t_win *win)
{
	if (win->flags->error_code == MAP_INVALID)
		ft_putstr_fd("MAP_INVALID", 2);
	if (win->flags->error_code == WIDTH_ERR)
		ft_putstr_fd("WIDTH_ERR", 2);
	if (win->flags->error_code == READ_ERR)
		ft_putstr_fd("FILE_ERR", 2);
	if (win->flags->error_code == COLOR_ERR)
		ft_putstr_fd("COLOR_ERR", 2);
	if (win->flags->error_code && errno)
		ft_putstr_fd(" - ", 2);
	if (errno)
		ft_putstr_fd(strerror(errno), 2);
	if (win->flags->error_code || errno)
		ft_putstr_fd("\n", 2);
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
