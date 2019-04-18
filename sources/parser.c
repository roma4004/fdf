/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/18 12:55:22 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_px				set_px(double x, double y, double z, unsigned int color)
{
	return ((t_px){
					(t_db_3pt){ x, y, z },
					z,
					color });
}

static unsigned int		parse_color(t_flags *flags, char *s,
									size_t *i, size_t max_i)
{
	unsigned int	res;
	size_t			j;

	res = DEF_COLOR;
	j = UINT64_MAX;
	if (max_i > *i + 3
	&& s && s[*i + ++j] == ',' && s[*i + ++j] == '0' && s[*i + ++j] == 'x')
	{
		while (max_i > *i + ++j && ft_ishex(s[*i + j]))
			if (j > 10)
			{
				flags->error_code = COLOR_ERR;
				return (DEF_COLOR);
			}
		res = (unsigned int)ft_atol_base(s + *i + 1, 16);
		(*i) += j;
	}
	return (res);
}

static int				parse_map(t_px ***map, t_param param,
									t_flags *flags, t_list *lst)
{
	char		*str;
	size_t		i;
	size_t		y;
	size_t		x;

	if (!lst)
		return (1);
	y = UINT64_MAX;
	if ((*map = (t_px **)malloc(sizeof(t_px *) * param.rows)))
		while (lst)
		{
			(*map)[++y] = (t_px *)malloc(sizeof(t_px) * param.cols);
			str = (char *)lst->content;
			x = UINT64_MAX;
			i = UINT64_MAX;
			while (lst->content_size > ++i && param.width > ++x)
				(*map)[y][x] = set_px(x, y,
						ft_iatoi(str, &i, lst->content_size),
						parse_color(flags, str, &i, lst->content_size));
			lst = lst->next;
		}
	return (0);
}

static int				validate_and_set_map_param(t_env *e, t_list *lst)
{
	size_t		width;
	size_t		i;
	char		*str;

	if (!lst || !e)
		return (1);
	while (lst)
	{
		str = (char *)lst->content;
		i = UINT64_MAX;
		while (i < lst->content_size)
			if (!(str[i] == ' ') || !(str[i] == ',') || !(str[i] == 'x')
			|| !(ft_ishex(str[++i])))
				return ((e->flags.error_code = MAP_INVALID));
		width = ft_count_words((char *)lst->content, lst->content_size, ' ');
		if (e->param.cols == 0)
			e->param.cols = width;
		else if (!WIDTH_ERR_SKIP && e->param.cols != width)
			e->flags.error_code = WIDTH_ERR;
		lst = lst->next;
	}
	if (!WIDTH_ERR_SKIP && 0 == e->param.cols)
		return ((e->flags.error_code = WIDTH_ERR));
	e->param.center = (t_db_2pt){ e->param.cols / 2.f, e->param.rows / 2.f };
	return (e->flags.error_code);
}

int						parse_file(t_env *e, char *file_name)
{
	int			fd;
	t_list		*lst;
	char		*buf;

	if (!e || !file_name)
		return (1);
	lst = NULL;
	if (-1 == (fd = open(file_name, O_RDONLY))
	|| ITS_A_DIRECTORY == errno)
		return ((e->flags.error_code = READ_ERR));
	while (0 < get_next_line(fd, &buf)
	&& ft_lstappend(&lst, buf, ft_strlen(buf))
	&& ++e->param.rows)
		ft_memdel((void *)&buf);
	close(fd);
	if (!lst && !errno && !WIDTH_ERR_SKIP)
		return ((e->flags.error_code = WIDTH_ERR));
	if (validate_and_set_map_param(e, lst) || e->flags.error_code
	|| parse_map(&e->map, e->param, &e->flags, lst) || ft_destroy_lst(lst))
		return (e->flags.error_code);
	return (0);
}
