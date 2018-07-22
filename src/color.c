/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/22 14:33:59 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		is_hex(char ch)
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

int		ch2int(char ch)
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

int		parse_color(char *hex, size_t *i, size_t max_i)
{
	int		res;

	res = 0;
	if (*i >= max_i || *i + 9 >= max_i || !hex || hex[0] != ',' 
	|| hex[1] != '0' || hex[2] != 'x'
	|| !is_hex(hex[3]) || !is_hex(hex[4]) 
	|| !is_hex(hex[5]) || !is_hex(hex[6])
	|| !is_hex(hex[7]) || !is_hex(hex[8]))
		return (DEF_COLOR);  //printf("col=%c%c%c%c%c%c%c%c", hex[1], hex[2], hex[3], hex[4], hex[5], hex[5], hex[6], hex[7]);
	if (*i + 11 < max_i && is_hex(hex[9]) && is_hex(hex[10]))
	{		
		res = ch2int(hex[3]) * 268435456	+ ch2int(hex[4])  * 16777216
			+ ch2int(hex[5]) * 1048576		+ ch2int(hex[6])  * 65536
			+ ch2int(hex[7]) * 4096			+ ch2int(hex[8])  * 256
			+ ch2int(hex[9]) * 16			+ ch2int(hex[10]) * 1;
		*i = *i + 11;
	}
	else
	{
		res = ch2int(hex[3]) * 1048576		+ ch2int(hex[4]) * 65536
			+ ch2int(hex[5]) * 4096			+ ch2int(hex[6]) * 256
			+ ch2int(hex[7]) * 16			+ ch2int(hex[8]) * 1;
		*i = *i + 9;
	}
	return (res);
}