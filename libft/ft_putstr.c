/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:45:36 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/01 13:50:24 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr(char const *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

void	ft_putstr_to(char const *s, int stream_num)
{
	if (!s)
		return ;
	write(stream_num, s, ft_strlen(s));
}