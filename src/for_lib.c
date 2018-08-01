/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:31:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/01 15:56:53 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		ft_destroy_lst(t_list *lst)
{
	t_list	*cur;
	t_list	*tmp;

	if (!(cur = lst))
		return (1);
	while (cur)
	{
		tmp = cur->next;
		if (cur->content)
			ft_memdel(&cur->content);
		ft_memdel((void *)&cur);
		cur = tmp;
	}
	return (0);
}

int			ft_lst_append(t_list **lst, char *buf, size_t size)
{
	t_list *cur;

	if (*lst == NULL)
		*lst = ft_lstnew(buf, size);
	else
	{
		cur = *lst;
		while (cur->next)
			cur = cur->next;
		cur->next = ft_lstnew(buf, size);
	}
	return (1);
}

long long	ft_i_atoi(const char *str, size_t *i, size_t max_i)
{
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	while (*i < max_i
		&& (str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\r'
			|| str[*i] == ' ' || str[*i] == '\v' || str[*i] == '\f'))
		*i = *i + 1;
	if (*i < max_i && (str[*i] == '-'))
		sign = -1;
	if (*i < max_i && (str[*i] == '-' || str[*i] == '+'))
		*i = *i + 1;
	while (*i < max_i && str[*i] >= '0' && str[*i] <= '9')
		result = result * 10 + (int)str[(*i)++] - '0';
	if (result > 9223372036854775807U && sign == 1)
		return (-1);
	if (result > 9223372036854775808U && sign == -1)
		return (0);
	return (result * sign);
}

static long long ft_atol_base2(const char *str, int base)
{
	long long		res;
	char		*dig;
	char		*tmp;
	int			i;

	dig = "0123456789abcdefghijklmnopqrstuvwxyz";
	res = 0;
	i = 0;
	while (str[i] && (tmp = (char *)ft_memchr(dig, ft_tolower(str[i]), base)))
	{
		res = (res * base) + (tmp - dig);
		i++;
	}
	return (res);
}

long long	ft_atol_base(const char *str, int base)
{
	long long	result;
	char		sign;
	int			i;

	sign = 1;
	i = 0;
	result = 0;
	if (!str || base < 2 || base > 36)
		return (result);
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	sign = (base == 10 && str[i] == '-') ? -1 : 1;
	if (base == 10 && (*str == '-' || *str == '+'))
		i++;
	if (base == 16 && str[i] == '0' && ft_tolower(str[i + 1]) == 'x')
		result = ft_atol_base2(str + 2, base);
	else
		result = ft_atol_base2(str, base);
	return (result * sign);
}
