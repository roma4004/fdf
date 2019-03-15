/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/15 16:41:38 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	set_px(t_env *win, t_ui_pt pt, long long z, int color)
{
	if (!win)
		return (0);
	win->map[pt.y][pt.x].x = pt.x;
	win->map[pt.y][pt.x].y = pt.y;
	win->map[pt.y][pt.x].z = z;
	win->map[pt.y][pt.x].z_orig = z;
	win->map[pt.y][pt.x].color = color;
	return (1);
}

static int	convert_map(t_env *win, t_list *lst)
{
	t_list		*cur;
	char		*str;
	size_t		i;
	t_ui_pt		pt;

	if (!win || !(cur = lst))
		return (1);
	pt.y = UINT32_MAX;
	if ((win->map = (t_px **)malloc(sizeof(t_px *) * win->param.rows)))
		while (cur && (str = (char *)cur->content))
		{
			if ((pt.x = UINT32_MAX)
			&& !(win->map[++pt.y] =
					(t_px *)malloc(sizeof(t_px) * win->param.cols)))
				return (1);
			i = UINT64_MAX;
			while (++i < cur->content_size && ++pt.x < win->param.width)
				set_px(win, pt, ft_i_atoi(str, &i, cur->content_size),
					get_col(win, str + i, &i, cur->content_size));
			cur = cur->next;
		}
	return (0);
}

static int	is_invalid_row(t_env *win, void *cont, size_t max_i)
{
	size_t	i;
	char	*str;

	if (!win || !(str = (char *)cont))
		return (0);
	i = UINT64_MAX;
	while (i < max_i)
		if (!(is_hex(str[++i])) || !(str[i] == ' ') || !(str[i] == 'x'))
			win->flags.error_code = MAP_INVALID;
	if (win->flags.error_code)
		return (1);
	return (0);
}

static int	get_map_param(t_env *win, t_list *lst)
{
	t_list *cur;
	size_t width;

	if (!(cur = lst) || !win)
		return (1);
	while (cur)
	{
		if (is_invalid_row(win, cur->content, cur->content_size))
			break ;
		width = ft_count_words((char *)cur->content, cur->content_size, ' ');
		if (win->param.cols == 0)
			win->param.cols = width;
		else if (win->param.cols != width && !WIDTH_ERR_SKIP)
			win->flags.error_code = WIDTH_ERR;
		cur = cur->next;
	}
	if (win->param.cols == 0 && !WIDTH_ERR_SKIP)
	{
		win->flags.error_code = WIDTH_ERR;
		return (1);
	}
	win->param.centr = (t_db_2pt){ win->param.rows / 2.f,
									win->param.cols / 2.f };
	return (0);
}

t_env		*parse_map(char *file_name, t_env *env)
{
	int		fd;
	t_list	*lst;
	char	*buf;

	if (!env || !file_name)
		return (NULL);
	lst = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1 || errno == ITS_A_DIRECTORY)
	{
		env->flags.error_code = READ_ERR;
		return (NULL);
	}
	while (get_next_line(fd, &buf) > 0
	&& (ft_lstappend(&lst, buf, ft_strlen(buf)))
	&& (++env->param.rows))
		ft_memdel((void *)&buf);
	close(fd);
	if (!lst && !(errno) && !WIDTH_ERR_SKIP)
		env->flags.error_code = WIDTH_ERR;
	if (get_map_param(env, lst) || env->flags.error_code
	|| convert_map(env, lst) || ft_destroy_lst(lst))
		return (NULL);
	return (env);
}
