/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:31:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/22 14:31:43 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_destroy_lst(t_list *lst)
{
	t_list	*cur;
	t_list	*tmp;

	if (!(cur = lst))
		return ;
	while (cur)
	{
		tmp = cur->next;
		if (cur->content)
			free(cur->content);
		free(cur);
		cur = tmp;
	}
}

int		ft_lst_append(t_list **lst, char *buf, int size)
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
	while ((str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\r' ||
			str[*i] == ' ' || str[*i] == '\v' || str[*i] == '\f') && *i < max_i)
		*i = *i + 1;
	if (str[*i] == '-')
		sign = -1;
	if (str[*i] == '-' || str[*i] == '+')
		*i = *i + 1;
	while (str[*i] >= '0' && str[*i] <= '9' && *i < max_i)
		result = result * 10 + (int)str[(*i)++] - '0';
	if (result > 9223372036854775807U && sign == 1)
		return (-1);
	if (result > 9223372036854775808U && sign == -1)
		return (0);
	return (result * sign);
}

size_t	ft_cnt_words(char *str, size_t max_i, char ch)
{
	size_t	i;
	size_t	num;

	if (str == NULL)
		return (0);
	i = -1;
	num = 0;
	while (++i < max_i && str[i])
		if (str[i] == ch && str[i + 1] != ch)
			num++;
	if (str[0] != '\0')
		num++;
	return (num);
}
