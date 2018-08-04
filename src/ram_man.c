/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:23:50 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/03 13:58:58 by dromanic         ###   ########.fr       */
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
		ft_memdel((void *)&win);
		return (1);
	}
	return (0);
}
