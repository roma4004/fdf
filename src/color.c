/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/02 21:47:45 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	is_hex(char ch)
{
	if ((ch >= '0' && ch <= '9')
		|| (ch >= 'A' && ch <= 'F')
		|| (ch >= 'a' && ch <= 'f'))
		return (1);
	return (0);
}

int			get_col(t_win *win, char *s, size_t *i, size_t max_i)
{
	int res;
	int j;

	res = DEF_COLOR;
	j = -1;
	if (*i + 3 < max_i && s && s[++j] == ',' && s[++j] == '0' && s[++j] == 'x')
	{
		while (*i + ++j < max_i && is_hex(s[j]))
			if (j > 10)
			{
				win->flags->error_code = COLOR_ERR;
				return (DEF_COLOR);
			}
		*i = *i + j;
		res = ft_atol_base(s + 1, 16);
	}
	return (res);
}
