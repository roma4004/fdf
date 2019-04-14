/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/21 19:59:28 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	is_hex(char ch)
{
	if (ft_isdigit(ch)
	|| (ch >= 'A' && ch <= 'F')
	|| (ch >= 'a' && ch <= 'f'))
		return (1);
	return (0);
}

static int	get_col(t_env *win, char *s, size_t *i, size_t max_i)
{
	int		res;
	size_t	j;

	res = DEF_COLOR;
	j = UINT64_MAX;
	if (*i + 3 < max_i
		&& s && s[*i + ++j] == ',' && s[*i + ++j] == '0' && s[*i + ++j] == 'x')
	{
		while (*i + ++j < max_i && is_hex(s[*i + j]))
			if (j > 10)
			{
				win->flags.error_code = COLOR_ERR;
				return (DEF_COLOR);
			}
		res = (int)ft_atol_base(s + *i + 1, 16);
		(*i) += j;
	}
	return (res);
}

static int	convert_map(t_env *e, t_list *lst)
{
	t_list		*cur;
	char		*str;
	size_t		i;
	t_si_3pt	pt;

	if (!e || !(cur = lst))
		return (1);
	pt.y = -1;
	if ((e->map = (t_px **)malloc(sizeof(t_px *) * e->param.rows)))
		while (cur && (str = (char *)cur->content))
		{
			if ((pt.x = -1)
			& !(e->map[++pt.y] = (t_px *)malloc(sizeof(t_px) * e->param.cols)))
				return (1);
			i = UINT64_MAX;
			while (++i < cur->content_size && ++pt.x < e->param.width)
				e->map[pt.y][pt.x] = (t_px){
					(t_db_3pt){ pt.x, pt.y,
								(pt.z = ft_iatoi(str, &i, cur->content_size)) },
								pt.z, get_col(e, str, &i, cur->content_size) };
			cur = cur->next;
		}
	return (0);
}

static int	get_map_param(t_env *e, t_list *lst)
{
	t_list	*cur;
	size_t	width;
	size_t	i;
	char	*str;

	if (!(cur = lst) || !e)
		return (1);
	while (cur && (str = (char *)cur->content))
	{
		i = UINT64_MAX;
		while (i < cur->content_size)
			if (!(str[i] == ' ') || !(str[i] == ',') || !(str[i] == 'x')
			|| !(is_hex(str[++i])))
				return ((e->flags.error_code = MAP_INVALID));
		width = ft_count_words((char *)cur->content, cur->content_size, ' ');
		if (e->param.cols == 0)
			e->param.cols = width;
		else if (e->param.cols != width && !WIDTH_ERR_SKIP)
			e->flags.error_code = WIDTH_ERR;
		cur = cur->next;
	}
	if (e->param.cols == 0 && !WIDTH_ERR_SKIP)
		return ((e->flags.error_code = WIDTH_ERR));
	e->param.centr = (t_db_2pt){ e->param.rows / 2.f, e->param.cols / 2.f };
	return (e->flags.error_code);
}

int			parse_map(char *file_name, t_env *env)
{
	int		fd;
	t_list	*lst;
	char	*buf;

	if (!env || !file_name)
		return (1);
	lst = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1
	|| errno == ITS_A_DIRECTORY)
		return ((env->flags.error_code = READ_ERR));
	while (get_next_line(fd, &buf) > 0
	&& (ft_lstappend(&lst, buf, ft_strlen(buf)))
	&& (++env->param.rows))
		ft_memdel((void *)&buf);
	close(fd);
	if (!lst && !(errno) && !WIDTH_ERR_SKIP)
		return ((env->flags.error_code = WIDTH_ERR));
	if (get_map_param(env, lst) || env->flags.error_code
	|| convert_map(env, lst) || ft_destroy_lst(lst))
		return (env->flags.error_code);
	return (0);
}
