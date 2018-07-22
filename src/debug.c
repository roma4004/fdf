/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:26:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/22 14:26:05 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_content_lst(t_list *lst)
{
	size_t	i;
	char	*s;
	t_list	*cur;

	if (!(cur = lst))
		return ;
	while (cur)
	{
		i = 0;
		s = (char *)cur->content;
		while (i < cur->content_size)
			printf("%c", s[i++]);
		printf("\n");
		cur = cur->next;
	}
}

void 	print_map(t_win *win)
{
	t_line	*line;
	size_t	y;
	size_t	x;

	line = (t_line *)malloc(sizeof(t_line));
/*
	line->end_y = 500;
	line->end_x = 500;
	draw_line(win, line, 100, 100, DEF_COLOR);

	line->end_y = 600;
	line->end_x = 150;
	draw_line(win, line, 100, 500, DEF_COLOR);

	line->end_y = 200;
	line->end_x = 200;
	draw_line(win, line, 200, 500, DEF_COLOR);

	line->end_y = 200;
	line->end_x = 200;
	draw_line(win, line, 500, 200, DEF_COLOR);
*/
	y = 0;
	while (y < win->map_rows)
	{
		x = 0;
		while (x < win->map_cols)
			draw_px_by_map(win, y, x++);
		y++;
	}
	free(line);
}
