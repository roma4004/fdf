/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/24 14:49:03 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void    dislpay_interface(t_win *win)
{
    mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 10, DEF_COLOR,
        "move             : arrows left, up, down, right");
    mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 30, DEF_COLOR,
        "zoom all         : -, + (or mouse scroll)");
    mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 50, DEF_COLOR,
        "zoom only Z      : numpad +, -");
    mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 70, DEF_COLOR,
        "interface        : numpad 7");
    mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 90, DEF_COLOR,
        "rotate Y,X,Z(+-) : QA, WS, ED");
    mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 130, DEF_COLOR,
        "reset angle      : R");
    mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 150, DEF_COLOR,
        "connection style : numpad 1..6 (|, /, -, \\, fdf, layer)");
    mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 110, DEF_COLOR,
        "next style       : enter (or hold to animate)");
}