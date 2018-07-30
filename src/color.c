/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/30 21:02:04 by dromanic         ###   ########.fr       */
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

int			pow_of(char ch, int pow)
{
	int res;

	res = 0;
	if (pow == 0)
		res += ch2int(ch) * 1;
	else if (pow == 1)
		res += ch2int(ch) * 16;
	else if (pow == 2)
		res += ch2int(ch) * 256;
	else if (pow == 3)
		res += ch2int(ch) * 4096;
	else if (pow == 4)
		res += ch2int(ch) * 65536;
	else if (pow == 5)
		res += ch2int(ch) * 1048576;
	else if (pow == 6)
		res += ch2int(ch) * 16777216;
	else if (pow == 7)
		res += ch2int(ch) * 268435456;
	return (res);
}

int			get_col(t_win *win, char *s, size_t *i, size_t max_i)
{
	int res;
	int j;
	int pow;

	res = 0;
	j = -1;
	pow = 0;
	if (*i + 3 < max_i && s && s[++j] == ',' && s[++j] == '0' && s[++j] == 'x')
	{
		while (*i + ++j < max_i && is_hex(s[j]))
			if (j > 10)
			{
				win->flags->error_code = COLOR_ERR;
				return (DEF_COLOR);
			}
		*i = *i + j;
		while (--j > 2)
			res += pow_of(s[j], pow++);
	}
	else
		res = DEF_COLOR;
	return (res);
}
