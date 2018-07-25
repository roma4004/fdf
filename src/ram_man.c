/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:23:50 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/22 14:23:53 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_map(t_win *win)
{
	size_t	i;
	size_t	j;

	if (win)
	{
		i = 0;
		while (i < win->param->rows)
		{
			j = 0;
			while (j < win->param->cols)
			{
				ft_memdel((void *)&win->map[i][j++]);
			}
			ft_memdel((void *)&win->map[i++]);
		}
		ft_memdel((void *)&win->map);
	}
}

int		free_win(t_win *win)
{
	if (win)
	{
		free_map(win);
		ft_memdel((void *)&win->param);
		ft_memdel((void *)&win->flags);
		ft_memdel((void *)&win);
		return (1);
	}
	return (0);
}
