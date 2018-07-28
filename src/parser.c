/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/28 20:14:09 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int convert_map(t_win *win, t_list *lst)
{
	t_list *cur;
	char   *str;
	size_t i;
	int    y;
	int    x;

	if (!win || !(cur = lst)
		|| !(y = -1))
		return (1);
	if ((win->map = (t_px **) malloc(sizeof(t_px *) * win->param->rows)))
		while (cur && cur->content && (str = (char *) cur->content))
		{
			if ((!(win->map[++y] =
						   (t_px *) malloc(sizeof(t_px) * win->param->cols))
				 || !(x = -1)
				 || !(i = -1)) && free_win(win))
				return (1);
			while (++i < cur->content_size)
			{
				set_vec(win, ++x, y, ft_i_atoi(str, &i, cur->content_size));
				win->map[y][x].color =
						get_col(win, str + i, &i, cur->content_size);
			}
			cur = cur->next;
		}
	return (0);
}

static int get_map_param(t_win *win, t_list *lst)
{
	t_list *cur;

	if (!(cur = lst) || !win)
		return (1);
	while (cur)
	{
		if (win->param->cols == 0)
			win->param->cols =
					ft_cnt_words((char *) cur->content, cur->content_size, ' ');
		else if (win->param->cols !=
				 ft_cnt_words((char *) cur->content, cur->content_size, ' '))
			win->flags->error_code = WIDTH_ERR;
		cur = cur->next;
	}
	if (win->flags->error_code)
		return (1);
	win->param->centr_y = win->param->rows / 2;
	win->param->centr_x = win->param->cols / 2;
	return (0);
}

int is_valid_map(t_win *win)
{
	//validate symbols
	return (1);
}

t_win *parse_map(char *file_name, t_win *win)
{
	int    fd;
	t_list *lst;
	char   *buf;

	if (!win || !file_name)
		return (NULL);
	lst     = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		win->flags->error_code = FILE_ERR;
		return (NULL);
	}
	while (get_next_line(fd, &buf) && (ft_lst_append(&lst, buf, ft_strlen(buf)))
	&& (++win->param->rows))
		ft_memdel((void *) &buf);
	if (get_map_param(win, lst) || win->flags->error_code || !is_valid_map(win)
	|| win->flags->error_code || convert_map(win, lst) || ft_destroy_lst(lst))
	{
		free_win(win);
		return (NULL);
	}
	if (fd != -1)
		close(fd);
	if (win->flags->error_code)
		return (NULL);
	return (win);
}
