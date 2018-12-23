/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:23:50 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 21:15:56 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_map(t_win *win)
{
	size_t	i;

	if (win)
	{
		i = -1;
		while (++i < win->param->rows)
			ft_memdel((void *)&win->map[i]);
		ft_memdel((void *)&win->map);
	}
}

int		free_win(t_win *win)
{
	if (win)
	{
		if (win->flags && win->map
			&& win->flags->error_code != WIDTH_ERR
			&& win->flags->error_code != MAP_INVALID)
			free_map(win);
		else
			win->map = NULL;
		if (win->param)
			ft_memdel((void *)&win->param);
		ft_memdel((void *)&win->flags);
		ft_memdel((void *)&win->img);
		ft_memdel((void *)&win);
		return (1);
	}
	return (0);
}

t_win	*clear_img(t_win *win)
{
	int y;
	int x;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			win->img->data[y * WIN_WIDTH + x] = 0;
	}
	return (win);
}
