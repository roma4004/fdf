/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/22 15:22:31 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int     deal_keyboard(int key, t_win *win)
{
    if (!win)
        return (1);
    if (key == 123)    
        map_offset(win, 0, -10);
    else if (key == 126)
        map_offset(win, -10, 0);
    else if (key == 125)
        map_offset(win, 10, 0);
    else if (key == 124)
        map_offset(win, 0, 10);
    else if (key == 78)
        zoom_offset(win, -10, 1);
    else if (key == 69)
        zoom_offset(win, +10, 1);
    else if (key == 36)
        animate(win);
    else if (key == 27)
        zoom_offset(win, -10, 0);
    else if (key == 24)
        zoom_offset(win, 10, 0);
    else
        deal_keyboard2(key, win);
    return (0);
}

int     deal_keyboard2(int key, t_win *win)
{
    if (!win)
        return (1);
    if (key == 83)
        numpads(win, 1);
    else if (key == 84)
        numpads(win, 2);
    else if (key == 85)
        numpads(win, 3);
    else if (key == 86)
        numpads(win, 4);
    else if (key == 87)
        numpads(win, 5);
    else if (key == 88)
        numpads(win, 6);
    else
        deal_keyboard3(key, win);
    return (0);
}

int     deal_keyboard3(int key, t_win *win)
{
    if (!win)
        return (1);
    if (key == 12)
        angle_change(win, 'y', 1);
    else if (key == 13)
        angle_change(win, 'x', 1);
    else if (key == 14)
        angle_change(win, 'z', 1);
    else if (key == 0)
        angle_change(win, 'y', -1);
    else if (key == 1)
        angle_change(win, 'x', -1);
    else if (key == 2)
        angle_change(win, 'z', -1);
    else if (key == 15)
        angle_reset(win);
    return (0);
}

int     deal_mouse(int key, int x, int y, t_win *win)
{
    if (!win)
        return (1);
    y++;
    x++;
    if (key == 4)
        zoom_offset(win, -1, 0);
    else if (key == 5)
        zoom_offset(win, 1, 0);
    return (0);
}