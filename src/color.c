/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/29 19:30:12 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	is_hex(char ch)
{
	if (ch == 'A' || ch == 'a'
		|| ch == 'B' || ch == 'b'
		|| ch == 'C' || ch == 'c'
		|| ch == 'D' || ch == 'd'
		|| ch == 'E' || ch == 'e'
		|| ch == 'F' || ch == 'f'
		|| (ch >= '0' && ch <= '9'))
		return (1);
	return (0);
}

static int	ch2int(char ch)
{
	if (ch == 'A' || ch == 'a')
		return (10);
	else if (ch == 'B' || ch == 'b')
		return (11);
	else if (ch == 'C' || ch == 'c')
		return (12);
	else if (ch == 'D' || ch == 'd')
		return (13);
	else if (ch == 'E' || ch == 'e')
		return (14);
	else if (ch == 'F' || ch == 'f')
		return (15);
	return (ch - '0');
}

int			get_col(t_win *win, char *s, size_t *i, size_t max_i)
{
	int res;

	res = DEF_COLOR;
	if (*i < max_i && *i + 9 < max_i && s && s[0] == ',')
	{
		if (s[1] != '0' || s[2] != 'x' || !is_hex(s[3]) || !is_hex(s[4])
			|| !is_hex(s[5]) || !is_hex(s[6]) || !is_hex(s[7]) || !is_hex(s[8]))
			win->flags->error_code = COLOR_ERR;
		if (*i + 11 < max_i && is_hex(s[9]) && is_hex(s[10]))
		{
			res = ch2int(s[3]) * 268435456 + ch2int(s[4]) * 16777216
				+ ch2int(s[5]) * 1048576 + ch2int(s[6]) * 65536
				+ ch2int(s[7]) * 4096 + ch2int(s[8]) * 256
				+ ch2int(s[9]) * 16 + ch2int(s[10]) * 1;
			*i = *i + 11;
		}
		else
		{
			res = ch2int(s[3]) * 1048576 + ch2int(s[4]) * 65536
				+ ch2int(s[5]) * 4096 + ch2int(s[6]) * 256
				+ ch2int(s[7]) * 16 + ch2int(s[8]) * 1;
			*i = *i + 9;
		}
	}
	return (res);
}
