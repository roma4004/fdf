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

int     toggle_param(int *param)
{
    if (*param == 0)
        *param = 1;
    else 
        *param = 0;
    return (1);
}

int     deal_key(int key, t_win *win)
{    printf("key: %d\n", key);
    if (key == 83)
        numpads(win, 1);
    if (key == 84)
        numpads(win, 2);
    if (key == 85)
        numpads(win, 3);
    if (key == 86)
        numpads(win, 4);
    if (key == 87)
        numpads(win, 5);
    if (key == 88)
        numpads(win, 6);
    /*if (key == 89)
        numpad(win);
    if (key == 90)
        numpad(win);
    if (key == 91)
        numpad(win);*/
    if (key == 36)
        animate(win);
    if (key == 27)
        zoom_offset(win, -10);
    if (key == 24)
        zoom_offset(win, 10);
    if (key == 123)    
        map_offset(win, 0, -10);
    if (key == 126)
        map_offset(win, -10, 0);
    if (key == 125)
        map_offset(win, 10, 0);
    if (key == 124)
        map_offset(win, 0, 10);
    return (0);
}
