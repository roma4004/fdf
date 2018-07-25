/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/17 15:22:05 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	convert_map(t_win *win, t_list *lst)
{
	t_list	*cur;
	char	*str;
	size_t	i;
	int		y;
	int		x;

	if (!win || !(cur = lst)
	|| !(y = -1))
		return (1);
	if ((win->map = (t_px **)malloc(sizeof(t_px *) * win->param->rows)))
		while (cur && cur->content && (str = (char *)cur->content))
		{
			if ((!(win->map[++y] =
					(t_px *)malloc(sizeof(t_px) * win->param->cols))
				|| !(x = -1)
				|| !(i = -1)) && free_win(win))
				return (1);
			while (++i < cur->content_size)
			{
				set_vec(win, ++x, y, ft_i_atoi(str, &i, cur->content_size));
				win->map[y][x].color = get_col(str + i, &i, cur->content_size);
			}
			cur = cur->next;
		}
	return (0);
}

static int	get_map_param(t_win *win, t_list *lst)
{
	t_list	*cur;

	if (!(cur = lst) || !win)
		return (1);
	while (cur)
	{
		if (win->param->cols == 0)
			win->param->cols = ft_cnt_words((char *)cur->content,
											cur->content_size, ' ');
		else if (win->param->cols != ft_cnt_words((char *)cur->content,
													cur->content_size, ' '))
				return (1);
		cur = cur->next;
	}
	if (win->param->rows == 0 || win->param->cols == 0)
		return (1);
	win->param->centr_y = win->param->rows / 2;
	win->param->centr_x = win->param->cols / 2;
	return (0);
}

t_win		*parse_map(char *file_name, t_win *win)
{
	int		fd;
	t_list	*lst;
	char	*buf;

	if (!win || !file_name)
		return (NULL);
	lst = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		win->flags->error_code = FILE_ERR;
		return (NULL);
	}		
	while (get_next_line(fd, &buf)
		&& (ft_lst_append(&lst, buf, ft_strlen(buf))) && (++win->param->rows))
		free(buf);
	if (get_map_param(win, lst) || convert_map(win, lst))
	{
		win->flags->error_code = MAP_INVALID;
		return (NULL);
	}
	ft_destroy_lst(lst);
	if (fd != -1)
		close(fd);
	//if ()
	//	return (win);
	return (win);
}
