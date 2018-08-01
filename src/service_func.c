/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:23:35 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/01 18:59:02 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		toggle_param(int *param)
{
	*param = ((*param == 0) ? 1 : 0);
	return (1);
}

int		set_vec(t_win *win, long long x, long long y, long long z)
{
	if (!win || x < 0 || y < 0)
		return (0);
	win->map[y][x].x = x;
	win->map[y][x].y = y;
	win->map[y][x].z = z;
	win->map[y][x].z_orig = z;
	return (1);
}

size_t	ft_cnt_words(char *str, size_t max_i, char separator)
{
	size_t	i;
	size_t	num;

	if (str == NULL)
		return (0);
	i = 0;
	num = 0;
	if (str[0] != separator)
		num++;
	while (++i < max_i && str[i])

		if (str[i] != separator && str[i - 1] == separator)
			num++;
	return (num);
}
